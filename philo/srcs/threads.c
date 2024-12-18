/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/18 23:33:00 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	size_t	current_time;
	size_t	last_meal;

	pthread_mutex_lock(&philo->time_last_meal_mutex);
	last_meal = philo->time_last_meal;
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
	current_time = get_time_milliseconds();
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->someone_died || (current_time - \
		last_meal) > philo->rules->time_to_die)
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
	t_philo	*philos;
	int		i;

	philos = (t_philo *)arg;
	i = 0;
	while (!is_simulation_stopped(philos[0].rules))
	{
		i = 0;
		while (i < philos[0].rules->nb_of_philos)
		{
			if (check_death(&philos[i]))
			{
				stop_simulation(philos[0].rules);
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->time_last_meal_mutex);
	philo->time_last_meal = get_time_milliseconds();
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
	if (philo->id % 2)
		usleep(1000);
	while (!is_simulation_stopped(philo->rules))
	{
		philo_eat(philo);
		if (philo->meals_eaten >= philo->rules->nb_of_meals_needed \
		&& philo->rules->nb_of_meals_needed != -1)
		{
			stop_simulation(philo->rules);
			break ;
		}
		if (!is_simulation_stopped(philo->rules))
			philo_sleep(philo);
		if (!is_simulation_stopped(philo->rules))
			philo_think(philo);
	}
	return (NULL);
}

int	create_threads(t_rules *rules, t_philo *philos, pthread_t *threads)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	rules->start_time = get_time_milliseconds();
	while (i < rules->nb_of_philos)
	{
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	if (pthread_create(&monitor, NULL, monitor_routine, philos) != 0)
		return (1);
	pthread_detach(monitor);
	return (0);
}
