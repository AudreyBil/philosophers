/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:27 by abillote          #+#    #+#             */
/*   Updated: 2024/12/20 12:30:50 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_rules(t_rules *rules, t_philo **philos, int argc, char **argv)
{
	rules->nb_of_philos = ft_atoi(argv[1]);
	rules->time_to_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->someone_died = 0;
	rules->stop_simulation = 0;
	if (argc == 6)
		rules->nb_meals = ft_atoi(argv[5]);
	else
		rules->nb_meals = -1;
	if (rules->nb_meals == 0)
		return (1);
	*philos = malloc(sizeof(t_philo) * rules->nb_of_philos);
	if (!*philos)
		return (1);
	return (0);
}

int	init_mutex(t_rules *rules, t_fork **forks, int nb_philo)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&rules->death_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&rules->stop_mutex, NULL) != 0)
		return (1);
	*forks = malloc(sizeof(t_fork) * nb_philo);
	if (!*forks)
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
	int	i;

	i = 0;
	if (init_mutex(rules, forks, rules->nb_of_philos) != 0)
		return (1);
	while (i < rules->nb_of_philos)
	{
		if (pthread_mutex_init(&(*philos)[i].time_last_meal_mutex, NULL) != 0)
			return (1);
		(*philos)[i].left_fork = &(*forks)[i];
		(*philos)[i].right_fork = &(*forks)[(i + 1) % rules->nb_of_philos];
		(*philos)[i].id = i + 1;
		(*philos)[i].rules = rules;
		(*philos)[i].eaten = 0;
		(*philos)[i].time_last_meal = 0;
		i++;
	}
	return (0);
}
