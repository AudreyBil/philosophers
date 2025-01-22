/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2025/01/22 14:59:50 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mutex);
	if (get_t() - philo->last_meal > philo->rules->t_die)
	{
		pthread_mutex_unlock(&philo->last_meal_mutex);
		print_action("died", philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->last_meal_mutex);
// 	size_t	current_time;
// 	size_t	last_meal;


	// pthread_mutex_lock(&philo->last_meal_mutex);
	// last_meal = philo->last_meal;
	// current_time = get_t();
	// pthread_mutex_unlock(&philo->last_meal_mutex);
	// pthread_mutex_lock(&philo->rules->death_mutex);
	// if (philo->rules->someone_died || (current_time - \
	// 	last_meal) >= philo->rules->t_die)
	// {
	// 	if (!philo->rules->someone_died)
	// 	{
	// 		philo->rules->someone_died = 1;
	// 		pthread_mutex_lock(&philo->rules->write_mutex);
	// 		printf("%ld %d %s\n", current_time - philo->rules->start_time, \
	// 		philo->id, "died");
	// 		pthread_mutex_unlock(&philo->rules->write_mutex);
	// 	}
	// 	pthread_mutex_unlock(&philo->rules->death_mutex);
	// 	return (1);
	// }
	// pthread_mutex_unlock(&philo->rules->death_mutex);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_rules	*rules;
	int		i;

	rules = (t_rules *)arg;
	i = 0;
	while (!stopped(rules))
	{
		if (check_all_ate(rules))
		{
			stop_simulation(rules);
			return (NULL);
		}
		i = 0;
		while (i < rules->nbphilos && !stopped(rules))
		{
			if (check_death(&rules->philos[i]))
			{
				stop_simulation(rules);
				return (NULL);
			}
			usleep(1000);
			i++;
		}
	}
	return (NULL);
}


void	philo_actions(t_philo *ph)
{
	if (ph->left_fork->fork_id < ph->right_fork->fork_id)
	{
		pthread_mutex_lock(&ph->left_fork->mutex);
		pthread_mutex_lock(&ph->right_fork->mutex);
	}
	else
	{
		pthread_mutex_lock(&ph->right_fork->mutex);
		pthread_mutex_lock(&ph->left_fork->mutex);
	}
	print_action("has taken a fork", ph);
	print_action("has taken a fork", ph);
	pthread_mutex_lock(&ph->last_meal_mutex);
	print_action("is eating", ph);
	ph->last_meal = get_t();
	ph->eaten += 1;
	pthread_mutex_unlock(&ph->last_meal_mutex);
	precise_sleep(ph->rules->time_to_eat);
	pthread_mutex_unlock(&ph->left_fork->mutex);
	pthread_mutex_unlock(&ph->right_fork->mutex);
	print_action("is sleeping", ph);
	precise_sleep(ph->rules->time_to_sleep);
	print_action("is thinking", ph);
}

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	if (ph->id % 2 == 0)
		precise_sleep(1);
	pthread_mutex_lock(&ph->last_meal_mutex);
	ph->last_meal = get_t();
	pthread_mutex_unlock(&ph->last_meal_mutex);
	if (ph->rules->nbphilos == 1)
		return (one_philo_eat(ph));
	while (!stopped(ph->rules))
	{
		philo_actions(ph);
	}
	return (NULL);
}

int	create_threads(t_rules *rules, t_philo *philos, pthread_t *threads)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	rules->start_time = get_t();
	while (i < rules->nbphilos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (rules->nbphilos > 1)
	{
		if (pthread_create(&monitor, NULL, monitor_routine, rules) != 0)
			return (1);
		pthread_detach(monitor);
	}
	return (0);
}
