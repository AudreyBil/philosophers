/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:22:44 by abillote          #+#    #+#             */
/*   Updated: 2024/12/26 11:26:58 by abillote         ###   ########.fr       */
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
			break ;
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
