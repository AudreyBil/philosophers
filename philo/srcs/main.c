/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:12:14 by abillote          #+#    #+#             */
/*   Updated: 2024/12/18 23:33:02 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_all(t_philo *philos, t_fork *fork, pthread_t *threads, int status)
{
	int	i;

	i = 0;
	if (philos && philos[0].rules)
		stop_simulation(philos[0].rules);
	if (philos)
	{
		while (i < philos[0].rules->nb_of_philos)
		{
			pthread_mutex_destroy(&philos[i].time_last_meal_mutex);
			pthread_mutex_destroy(&philos[i].left_fork->mutex);
			i++;
		}
		pthread_mutex_destroy(&philos[0].rules->stop_mutex);
		pthread_mutex_destroy(&philos[0].rules->death_mutex);
		pthread_mutex_destroy(&philos[0].rules->write_mutex);
		free(philos);
	}
	if (fork)
		free(fork);
	if (threads)
		free(threads);
	exit(status);
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

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_rules(&rules, &philos, argc, argv) != 0)
		return (1);
	if (init_philo(&philos, &rules, &forks) != 0)
		free_all(philos, forks, NULL, EXIT_FAILURE);
	threads = malloc(sizeof(pthread_t) * rules.nb_of_philos);
	if (!threads)
		free_all(philos, forks, threads, EXIT_FAILURE);
	if (create_threads(&rules, philos, threads) != 0)
		free_all(philos, forks, threads, EXIT_FAILURE);
	i = 0;
	while (i < rules.nb_of_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	stop_simulation(&rules);
	free_all(philos, forks, threads, EXIT_SUCCESS);
}
