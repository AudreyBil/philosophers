/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:54:27 by abillote          #+#    #+#             */
/*   Updated: 2024/12/25 19:23:45 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_rules(t_rules *rules, int argc, char **argv)
{
	rules->nbphilos = ft_atoi(argv[1]);
	rules->t_die = ft_atoi(argv[2]);
	rules->time_to_eat = ft_atoi(argv[3]);
	rules->time_to_sleep = ft_atoi(argv[4]);
	rules->someone_died = 0;
	if (argc == 6)
		rules->nb_meals = ft_atoi(argv[5]);
	else
		rules->nb_meals = -1;
	if (rules->nb_meals == 0)
		return (1);
	rules->philos = malloc(sizeof(t_philo) * rules->nbphilos);
	if (!rules->philos)
		return (1);
	return (0);
}

int	init_sem(t_rules *rules)
{
	sem_unlink("deather");
	sem_unlink("writer");
	sem_unlink("forks");
	sem_unlink("eater");
	if ((rules->deather = sem_open("deather", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (1);
	if ((rules->writer = sem_open("writer", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (1);
	if ((rules->forks = sem_open("forks", O_CREAT, S_IRWXU, rules->nbphilos)) == SEM_FAILED)
		return (1);
	if ((rules->eater = sem_open("eater", O_CREAT, S_IRWXU, 1)) == SEM_FAILED)
		return (1);
	return (0);
}

int	init_philo(t_philo **philos, t_rules *rules)
{
	int	i;

	i = 0;
	if (init_sem(rules) != 0)
		return (1);
	while (i < rules->nbphilos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].rules = rules;
		(*philos)[i].eating_count = 0;
		(*philos)[i].last_meal = 0;
		i++;
	}
	return (0);
}
