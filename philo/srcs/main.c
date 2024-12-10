/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:12:14 by abillote          #+#    #+#             */
/*   Updated: 2024/12/10 21:56:42 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error : wrong number of arguments\n");
		printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep \
		[number_of_times_each_philosopher_must_eat]\n");
		return (1);
	}
	//make a look to check each args to spare lines
	if (ft_atoi(argv[1]) < 1)
	{
		printf("Error: You need at least one philosopher\n");
		return (0);
	}
	if (ft_atoi(argv[5] < 0))
	{
		printf("Error: You are asking for a negative number of meals\n");
		return (0);
	}
	if ()
}

void	init_philo(t_philo *philos, int argc, char **argv)
{
	philos->nb_of_philos = ft_atoi(argv[1]);
	philos->time_to_die = ft_atoi(argv[2]);
	philos->time_to_eat = ft_atoi(argv[3]);
	philos->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philos->nb_of_meals = ft_atoi(argv[5]);
	else
		philos->nb_of_meals = -1;
}

int	main(int argc, char **argv)
{
	t_philo	philos;

	if (!check_args(argc, argv))
		return (1);
	init_philo(&philos, argc, argv);

	printf("nb of philo is %d\n", philos.nb_of_philos);
	printf("time to die is %ld\n", philos.time_to_die);
}
