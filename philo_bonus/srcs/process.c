/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:06:19 by abillote          #+#    #+#             */
/*   Updated: 2024/12/26 11:36:21 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo)
{
	size_t	current_time;
	size_t	last_meal;

	sem_wait(philo->rules->eater);
	last_meal = philo->last_meal;
	sem_post(philo->rules->eater);
	current_time = get_t();
	sem_wait(philo->rules->deather);
	if (philo->rules->someone_died || (current_time - \
		last_meal) >= philo->rules->t_die)
	{
		if (!philo->rules->someone_died)
		{
			philo->rules->someone_died = 1;
			sem_wait(philo->rules->writer);
			printf("%ld %d %s\n", current_time - philo->rules->start_time, \
			philo->id, "died");
			sem_post(philo->rules->writer);
			exit (1);
		}
		sem_post(philo->rules->deather);
		return (1);
	}
	sem_post(philo->rules->deather);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->rules->eater);
		if (philo->eating_count >= philo->rules->nb_meals \
			&& philo->rules->nb_meals > 0)
		{
			sem_post(philo->rules->eater);
			break ;
		}
		sem_post(philo->rules->eater);
		if (check_death(philo))
			break ;
	}
	return (NULL);
}

void	philo_routine(t_rules *rules, t_philo *ph)
{
	ph->last_meal = get_t();
	pthread_create(&ph->monitor_thread, NULL, monitor_routine, ph);
	if (ph->id % 2)
		usleep(50000);
	while (1)
	{
		philo_eat(ph);
		sem_wait(rules->eater);
		if (rules->nb_meals > 0 && ph->eating_count >= rules->nb_meals)
		{
			sem_post(rules->eater);
			pthread_join(ph->monitor_thread, NULL);
			exit (0);
		}
		sem_post(rules->eater);
		philo_sleep(ph);
		philo_think(ph);
	}
	pthread_join(ph->monitor_thread, NULL);
	if (rules->someone_died == 1)
		exit(1);
	exit(0);
}

int	create_processes(t_rules *rules)
{
	int			i;

	i = 0;
	rules->start_time = get_t();
	while (i < rules->nbphilos)
	{
		rules->philos[i].process_id = fork();
		if (rules->philos[i].process_id < 0)
		{
			printf("Error creating child process\n");
			while (i >= 0)
			{
				kill(rules->philos[i].process_id, SIGKILL);
				i--;
			}
			return (1);
		}
		else if (rules->philos[i].process_id == 0)
			philo_routine(rules, &rules->philos[i]);
		i++;
	}
	return (0);
}
