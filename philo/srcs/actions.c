/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 18:21:21 by abillote          #+#    #+#             */
/*   Updated: 2024/12/16 15:07:31 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	print_action(" has taken a fork", philo);
	pthread_mutex_lock(&philo->right_fork->mutex);
	print_action(" has taken a fork", philo);
	print_action(" is eating", philo);
	usleep(philo->rules->time_to_eat * 1000);
	philo->time_last_meal = get_time_milliseconds();
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
	philo->meals_eaten++;
}

