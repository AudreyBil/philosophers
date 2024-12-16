/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/16 15:04:23 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;

	philo->time_last_meal = get_time_milliseconds();

	if (philo->id % 2)
		usleep(1000);
	//while (!check_death(philo))
	while(philo->meals_eaten < philo->rules->nb_of_meals_needed)
	{
		philo_eat(philo);
		if (philo->meals_eaten >= philo->rules->nb_of_meals_needed \
		&& philo->rules->nb_of_meals_needed != -1)
			break ;
		//philo_sleep(philo);
		//philo_think(philo);
	}
	return (NULL);
}

int	create_threads(t_rules *rules, t_philo *philos, pthread_t *threads)
{
	int	someone_died;
	int i;

	someone_died = 0;
	i = 0;
	rules->start_time = get_time_milliseconds();
	while (i < rules->nb_of_philos)
	{
		philos[i].someone_died = &someone_died;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}
