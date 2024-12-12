/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:27 by abillote          #+#    #+#             */
/*   Updated: 2024/12/12 18:04:48 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_rules(t_rules *rules, t_philo **philos, int argc, char **argv)
{
	rules->nb_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		rules->nb_of_meals = ft_atoi(argv[5]);
	else
		rules->nb_of_meals = -1;
	*philos = malloc(sizeof(t_philo) * rules->nb_of_philos);
	if (!philos)
		return (1);
	return (0);
}

int	init_mutex(pthread_mutex_t *death_mutex, pthread_mutex_t *write_mutex, \
				t_fork **forks, int nb_philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(write_mutex, NULL) != 0)
		return (1);
	*forks = malloc(sizeof(t_fork) * nb_philo);
	if (!forks)
		return (1);
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&(*forks)[i].mutex, NULL) != 0)
			return (1);
		(*forks)[i].fork_id = i;
		i++;
	}
	return (0);
}

int	init_philo(t_philo **philos, t_rules *rules, t_fork **forks)
{
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	write_mutex;
	int				i;

	i = 0;
	if (init_mutex(&death_mutex, &write_mutex, forks, rules->nb_of_philos) \
					!= 0)
	{
		free(philos);
		return (1);
	}
	while (i < rules->nb_of_philos)
	{
		philos[i]->death_mutex = &death_mutex;
		philos[i]->write_mutex = &write_mutex;
		philos[i]->left_fork = forks[i];
		philos[i]->right_fork = forks[(i + 1) % rules->nb_of_philos];
		philos[i]->id = i;
		i++;
	}
	return (0);
}
