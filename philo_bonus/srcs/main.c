/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:12:14 by abillote          #+#    #+#             */
/*   Updated: 2024/12/25 19:23:24 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	kill_processes(t_rules *rules)
{
	int	pid_return;
	int	i;

	i = 0;
	while (i < rules->nbphilos)
	{
		waitpid(-1, &pid_return, 0);
		if (pid_return != 0)
		{
			i = 0;
			while (i < rules->nbphilos)
			{
				kill(rules->philos[i].process_id, SIGKILL);
				i++;
			}
			break;
		}
		i++;
	}
}

void	clean_sem(t_rules *rules)
{
	sem_close(rules->deather);
	sem_close(rules->eater);
	sem_close(rules->forks);
	sem_unlink("deather");
	sem_unlink("eater");
	sem_unlink("forks");
}

int	free_all(t_rules *rules, int status)
{
	kill_processes(rules);
	clean_sem(rules);
	if (rules->philos)
		free(rules->philos);
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

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_rules(&rules, argc, argv) != 0)
		return (1);
	if (init_philo(&rules.philos, &rules) != 0)
		return (free_all(&rules, EXIT_FAILURE));
	if (create_processes(&rules) != 0)
		return (free_all(&rules, EXIT_FAILURE));
	return (free_all(&rules, EXIT_SUCCESS));
}
