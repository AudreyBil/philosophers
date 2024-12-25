/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:21:21 by abillote          #+#    #+#             */
/*   Updated: 2024/12/25 19:13:30 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	print_action(char *s, t_philo *ph)
{
	size_t	current_time;
	int		can_print;

	sem_wait(ph->rules->deather);
	can_print = (ph->rules->someone_died == 0);
	sem_post(ph->rules->deather);
	if (can_print)
	{
		sem_wait(ph->rules->writer);
		current_time = get_t();
		printf("%ld %d %s\n", current_time - ph->rules->start_time, ph->id, s);
		sem_post(ph->rules->writer);
	}
}

void	one_philo_eat(t_philo *ph)
{
	sem_wait(ph->rules->forks);
	print_action("has taken a fork", ph);
	sem_post(ph->rules->forks);
	usleep(ph->rules->t_die * 1000);
}

void	philo_eat(t_philo *ph)
{
	if (ph->rules->nbphilos == 1)
		return (one_philo_eat(ph));
	sem_wait(ph->rules->forks);
	print_action("has taken a fork", ph);
	sem_wait(ph->rules->forks);
	print_action("has taken a fork", ph);
	sem_wait(ph->rules->eater);
	ph->last_meal = get_t();
	ph->eating_count++;
	sem_post(ph->rules->eater);
	print_action("is eating", ph);
	usleep(ph->rules->time_to_eat * 1000);
	sem_post(ph->rules->forks);
	sem_post(ph->rules->forks);
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
