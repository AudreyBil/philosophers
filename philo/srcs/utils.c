/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:40:04 by abillote          #+#    #+#             */
/*   Updated: 2024/12/18 23:32:58 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		number;
	int		sign;

	i = 0;
	number = 0;
	sign = 1;
	while ((nptr[i] > 8 && nptr[i] < 14) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	number *= sign;
	return (number);
}

size_t	get_time_milliseconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	is_simulation_stopped(t_rules *rules)
{
	int	stopped;

	pthread_mutex_lock(&rules->stop_mutex);
	stopped = rules->stop_simulation;
	pthread_mutex_unlock(&rules->stop_mutex);
	return (stopped);
}

void	stop_simulation(t_rules *rules)
{
	pthread_mutex_lock(&rules->stop_mutex);
	rules->stop_simulation = 1;
	pthread_mutex_unlock(&rules->stop_mutex);
}
