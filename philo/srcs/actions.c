/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:21:21 by abillote          #+#    #+#             */
/*   Updated: 2024/12/20 13:53:03 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(char *s, t_philo *ph)
{
	size_t	current_time;
	int		can_print;

	pthread_mutex_lock(&ph->rules->death_mutex);
	can_print = (ph->rules->someone_died == 0);
	pthread_mutex_unlock(&ph->rules->death_mutex);
	if (can_print)
	{
		pthread_mutex_lock(&ph->rules->write_mutex);
		current_time = get_t();
		printf("%ld %d %s\n", current_time - ph->rules->start_time, ph->id, s);
		pthread_mutex_unlock(&ph->rules->write_mutex);
	}
}

void	one_philo_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->left_fork->mutex);
	print_action("has taken a fork", ph);
	usleep(ph->rules->t_die * 1000);
	pthread_mutex_unlock(&ph->left_fork->mutex);
}

void	philo_eat(t_philo *ph)
{
	if (ph->rules->nbphilos == 1)
		return (one_philo_eat(ph));
	if (ph->left_fork->fork_id < ph->right_fork->fork_id)
	{
		pthread_mutex_lock(&ph->left_fork->mutex);
		print_action("has taken a fork", ph);
		pthread_mutex_lock(&ph->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&ph->right_fork->mutex);
		print_action("has taken a fork", ph);
		pthread_mutex_lock(&ph->left_fork->mutex);
	}
	print_action("has taken a fork", ph);
	print_action("is eating", ph);
	pthread_mutex_lock(&ph->last_meal_mutex);
	ph->last_meal = get_t();
	pthread_mutex_unlock(&ph->last_meal_mutex);
	usleep(ph->rules->time_to_eat * 1000);
	ph->eaten++;
	pthread_mutex_unlock(&ph->right_fork->mutex);
	pthread_mutex_unlock(&ph->left_fork->mutex);
}

void	philo_sleep(t_philo *ph)
{
	print_action("is sleeping", ph);
	usleep(ph->rules->time_to_sleep * 1000);
}

void	philo_think(t_philo *ph)
{
	print_action("is thinking", ph);
}
