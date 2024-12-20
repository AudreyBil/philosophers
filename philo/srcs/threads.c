/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/20 12:44:44 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	size_t	current_time;
	size_t	last_meal;

	pthread_mutex_lock(&philo->time_last_meal_mutex);
	last_meal = philo->time_last_meal;
	current_time = get_time_ms();
	pthread_mutex_unlock(&philo->time_last_meal_mutex);
	pthread_mutex_lock(&philo->rules->death_mutex);
	if (philo->rules->someone_died || (current_time - \
		last_meal) >= philo->rules->time_to_die - 1)
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
		while (i < philos[0].rules->nb_of_philos && !is_simulation_stopped(philos[0].rules))
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
	t_philo	*ph;

	ph = (t_philo *)arg;
	pthread_mutex_lock(&ph->time_last_meal_mutex);
	ph->time_last_meal = get_time_ms();
	pthread_mutex_unlock(&ph->time_last_meal_mutex);
	if (ph->id % 2)
		usleep(1000);
	while (!is_simulation_stopped(ph->rules))
	{
		if ((get_time_ms() - ph->time_last_meal) < ph->rules->time_to_die)
			philo_eat(ph);
		if (ph->eaten >= ph->rules->nb_meals && ph->rules->nb_meals != -1)
		{
			stop_simulation(ph->rules);
			break ;
		}
		if (!is_simulation_stopped(ph->rules) && (get_time_ms() - ph->time_last_meal) < ph->rules->time_to_die)
			philo_sleep(ph);
		if (!is_simulation_stopped(ph->rules) && (get_time_ms() - ph->time_last_meal) < ph->rules->time_to_die)
			philo_think(ph);
	}
	return (NULL);
}

int	create_threads(t_rules *rules, t_philo *philos, pthread_t *threads)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	rules->start_time = get_time_ms();
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
