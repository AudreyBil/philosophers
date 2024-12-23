/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:12:14 by abillote          #+#    #+#             */
/*   Updated: 2024/12/23 18:37:47 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	free_all(t_rules *rules, t_fork *fork, pthread_t *threads, int status)
{
	int	i;

	i = 0;
	if (rules->philos)
		stop_simulation(rules);
	if (rules->philos)
	{
		while (i < rules->nbphilos)
		{
			pthread_mutex_destroy(&rules->philos[i].last_meal_mutex);
			pthread_mutex_destroy(&rules->philos[i].meal_count_mutex);
			pthread_mutex_destroy(&rules->philos[i].left_fork->mutex);
			i++;
		}
		pthread_mutex_destroy(&rules->stop_mutex);
		pthread_mutex_destroy(&rules->death_mutex);
		pthread_mutex_destroy(&rules->write_mutex);
		free(rules->philos);
	}
	if (fork)
		free(fork);
	if (threads)
		free(threads);
	return (status);
}

int	check_number_args(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error : wrong number of arguments\n");
		return (1);
	}
	return (0);
}

int	check_args(int argc, char **argv)
{
	int	i;

	i = 1;
	if (check_number_args(argc) == 1)
		return (1);
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
		if (i > 1 && i < 5 && ft_atoi(argv[i]) <= 0)
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
	pthread_t	*threads;
	t_fork		*forks;
	int			i;

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_rules(&rules, argc, argv) != 0)
		return (1);
	if (init_philo(&rules.philos, &rules, &forks) != 0)
		return (free_all(&rules, forks, NULL, EXIT_FAILURE));
	threads = malloc(sizeof(pthread_t) * rules.nbphilos);
	if (!threads)
		return (free_all(&rules, forks, threads, EXIT_FAILURE));
	if (create_threads(&rules, rules.philos, threads) != 0)
		return (free_all(&rules, forks, threads, EXIT_FAILURE));
	i = 0;
	while (i < rules.nbphilos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	stop_simulation(&rules);
	return (free_all(&rules, forks, threads, EXIT_SUCCESS));
}
