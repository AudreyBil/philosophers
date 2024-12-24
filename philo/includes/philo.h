/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:14:29 by abillote          #+#    #+#             */
/*   Updated: 2024/12/24 13:06:19 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

struct					s_rules;
struct					s_philo;
typedef struct s_philo	t_philo;

typedef struct s_fork{
	pthread_mutex_t	mutex;
	int				fork_id;
}	t_fork;

typedef struct s_philo {
	int				id;
	size_t			last_meal;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	meal_count_mutex;
	int				eaten;
	t_fork			*left_fork;
	t_fork			*right_fork;
	struct s_rules	*rules;

}	t_philo;

typedef struct s_rules {
	int				nbphilos;
	int				nb_meals;
	size_t			t_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	death_mutex;
	int				someone_died;
	int				stop_simulation;
	pthread_mutex_t	stop_mutex;
	t_philo			*philos;
}	t_rules;

//init.c
int		init_philo(t_philo **philos, t_rules *rules, t_fork **forks);
int		init_mutex(t_rules *rules, t_fork **forks, int nb_philo);
int		init_rules(t_rules *rules, int argc, char **argv);

//threads.c
int		create_threads(t_rules *rules, t_philo *philos, \
					pthread_t *threads);
void	*philo_routine(void *arg);
int		check_death(t_philo *philo);

//actions.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);

//utils.c
int		ft_atoi(const char *nptr);
size_t	get_t(void);
void	print_action(char *s, t_philo *philo);
void	stop_simulation(t_rules *rules);
int		stopped(t_rules *rules);
int		check_all_ate(t_rules *rules);

#endif
