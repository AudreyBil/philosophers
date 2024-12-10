/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:14:29 by abillote          #+#    #+#             */
/*   Updated: 2024/12/10 21:42:28 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct s_philo {
	int		nb_of_philos;
	int		id;
	int		nb_of_meals;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;

}	t_philo;

//utils.c
int	ft_atoi(const char *nptr);


#endif
