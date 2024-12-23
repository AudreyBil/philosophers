/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/23 19:30:45 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	size_t	current_time;
	size_t	last_meal;

	pthread_mutex_lock(&philo->last_meal_mutex);
	last_meal = philo->last_meal;
	current_time = get_t();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->someone_died || (current_time - \
		last_meal) >= philo->rules->t_die - 1)
	{
		if (!philo->rules->someone_died)
		{
			philo->rules->someone_died = 1;
			pthread_mutex_lock(&philo->rules->write_mutex);
			printf("%ld %d %s\n", current_time - philo->rules->start_time, \
			philo->id, "died");
			pthread_mutex_unlock(&philo->rules->write_mutex);
		}
		pthread_mutex_unlock(&philo->rules->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->rules->death_mutex);
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

void	*philo_routine(void *arg)
{
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_mutex_lock(&ph->last_meal_mutex);
	ph->last_meal = get_t();
	pthread_mutex_unlock(&ph->last_meal_mutex);
	if (ph->id % 2)
		usleep(15000);
	while (!stopped(ph->rules))
	{
		if ((get_t() - ph->last_meal) < ph->rules->t_die)
		{
			philo_eat(ph);
			pthread_mutex_lock(&ph->meal_count_mutex);
			ph->eaten++;
			pthread_mutex_unlock(&ph->meal_count_mutex);
		}
		if (!stopped(ph->rules) && (get_t() - ph->last_meal) < ph->rules->t_die)
			philo_sleep(ph);
		if (!stopped(ph->rules) && (get_t() - ph->last_meal) < ph->rules->t_die)
			philo_think(ph);
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
	if (pthread_create(&monitor, NULL, monitor_routine, rules) != 0)
		return (1);
	pthread_detach(monitor);
	return (0);
}
