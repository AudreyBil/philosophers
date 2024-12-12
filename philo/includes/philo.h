/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:14:29 by abillote          #+#    #+#             */
/*   Updated: 2024/12/12 18:34:14 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>

typedef struct s_fork{
	pthread_mutex_t	mutex;
	int				fork_id;
}	t_fork;

typedef struct s_rules {
	int		nb_of_philos;
	int		nb_of_meals_needed;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
}	t_rules;

typedef struct s_philo {
	int				id;
	size_t			time_last_meal;
	size_t			start_time;
	int				meals_eaten;
	int				eating_count;
	int				*someone_died;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	struct s_rules	*rules;

}	t_philo;

//init.c
int	init_philo(t_philo **philos, t_rules *rules, t_fork **forks);
int	init_mutex(pthread_mutex_t *death_mutex, pthread_mutex_t *write_mutex, \
				t_fork **forks, int nb_philo);
int	init_rules(t_rules *rules, t_philo **philos, int argc, char **argv);

//threads.c
int	create_threads(t_rules *rules, t_philo **philos, \
					pthread_t *threads, t_fork *forks);

//utils.c
int	ft_atoi(const char *nptr);

#endif
