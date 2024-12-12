/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/12 18:27:54 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	create_threads(t_rules *rules, t_philo **philos, pthread_t *threads, t_fork *forks)
{
	int	someone_died;
	int i;

	someone_died = 0;
	i = 0;
	threads = malloc(sizeof(pthread_t) * rules->nb_of_philos);
	if (!threads)
	{
		free(philos);
		free(forks);
		return (1);
	}
	while (i < rules->nb_of_philos)
	{
		philos[i]->someone_died = &someone_died;
		if (pthread_create(&threads[i], NULL, philo_routine, &philos[i]) != 0)
		{
			free(philos);
			free(forks);
			return (1);
		}
		i++;
	}
	return (0);
}
