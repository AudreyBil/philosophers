/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:14:29 by abillote          #+#    #+#             */
/*   Updated: 2024/12/18 17:49:15 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork{
	pthread_mutex_t	mutex;
	int				fork_id;
}	t_fork;

typedef struct s_rules {
	int				nb_of_philos;
	int				nb_of_meals_needed;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
}	t_rules;

typedef struct s_philo {
	int				id;
	size_t			time_last_meal;
	pthread_mutex_t	time_last_meal_mutex;
	int				meals_eaten;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_rules	*rules;

}	t_philo;

//init.c
int		init_philo(t_philo **philos, t_rules *rules, t_fork **forks);
int		init_mutex(t_rules *rules, t_fork **forks, int nb_philo);
int		init_rules(t_rules *rules, t_philo **philos, int argc, char **argv);

//threads.c
int		create_threads(t_rules *rules, t_philo *philos, \
					pthread_t *threads);
void	*philo_routine(void *arg);

//actions.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void    philosopher_wait(t_rules *rules, size_t wait_time);


//utils.c
int		ft_atoi(const char *nptr);
size_t	get_time_milliseconds(void);
void	print_action(char *s, t_philo *philo);
void	stop_simulation(t_rules *rules);
int		is_simulation_stopped(t_rules *rules);

#endif
