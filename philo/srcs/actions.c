/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:21:21 by abillote          #+#    #+#             */
/*   Updated: 2024/12/17 13:23:19 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(char *s, t_philo *philo)
{
	size_t	current_time;

	pthread_mutex_lock(&philo->rules->write_mutex);
	current_time = get_time_milliseconds();
	if (philo->rules->someone_died == 0)
		printf("%ld %d %s\n", current_time - philo->rules->start_time, \
			philo->id, s);
	pthread_mutex_unlock(&philo->rules->write_mutex);
}

void	one_philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_action("has taken a fork", philo);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	philo_eat(t_philo *philo)
{
	if (philo->rules->nb_of_philos == 1)
	{
		one_philo_eat(philo);
		return ;
	}
	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		pthread_mutex_lock(&philo->left_fork->mutex);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(&philo->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&philo->right_fork->mutex);
		print_action("has taken a fork", philo);
		pthread_mutex_lock(&philo->left_fork->mutex);
	}
	print_action("has taken a fork", philo);
	print_action("is eating", philo);
	philo->time_last_meal = get_time_milliseconds();
	usleep(philo->rules->time_to_eat * 1000);
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->right_fork->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
}

void	philo_sleep(t_philo *philo)
{
	print_action("is sleeping", philo);
	usleep(philo->rules->time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	print_action("is thinking", philo);
}
