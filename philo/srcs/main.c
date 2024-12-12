/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:12:14 by abillote          #+#    #+#             */
/*   Updated: 2024/12/12 18:34:05 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (i == 1 && ft_atoi(argv[i]) < 1)
		{
			printf("Error: Your philosopher number is wrong\n");
			return (1);
		}
		if (i == 5 && ft_atoi(argv[i]) < 0)
		{
			printf("Error: Your number of meals is wrong\n");
			return (1);
		}
		if (i > 1 && i < 5 && ft_atoi(argv[i]) < 0)
		{
			printf("Error: One your of your time has a wrong value\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rules		rules;
	t_philo		*philos;
	pthread_t	*threads;
	t_fork		*forks;
	int			i;

	if (argc != 5 && argc != 6)
	{
		printf("Error : wrong number of arguments\n");
		return (1);
	}
	if (check_args(argc, argv) != 0)
		return (1);
	if (init_rules(&rules, &philos, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &rules, &forks) != 0)
		return (1);
	if (create_threads(&rules, &philos, &threads, &forks) != 0)
		return (1);
	i = 0;
	while (i++ < rules.nb_of_philos)
		pthread_join(threads[i], NULL);
	free(philos);
	free(threads);
	free(forks);
}
