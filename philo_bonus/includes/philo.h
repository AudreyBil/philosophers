/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 21:14:29 by abillote          #+#    #+#             */
/*   Updated: 2024/12/25 19:23:04 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>

struct					s_rules;
struct					s_philo;
typedef struct s_philo	t_philo;

typedef struct s_philo {
	int				id;
	int				process_id;
	size_t			last_meal;
	pthread_t		monitor_thread;
	int				eating_count;
	struct s_rules	*rules;

}	t_philo;

typedef struct s_rules {
	int				nbphilos;
	int				nb_meals;
	size_t			t_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_time;
	sem_t			*writer;
	sem_t			*deather;
	sem_t			*forks;
	sem_t			*eater;
	int				someone_died;
	t_philo			*philos;
}	t_rules;

//init.c
int		init_philo(t_philo **philos, t_rules *rules);
int		init_sem(t_rules *rules);
int		init_rules(t_rules *rules, int argc, char **argv);

//process.c
int		create_processes(t_rules *rules);
void	philo_routine(t_rules *rules, t_philo *ph);
void	*monitor_routine(void *arg);
int		check_death(t_philo *philo);

//actions.c
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
void	print_action(char *s, t_philo *ph);


//utils.c
int		ft_atoi(const char *nptr);
size_t	get_t(void);
void	stop_simulation(t_rules *rules);
int		stopped(t_rules *rules);
int		check_all_ate(t_rules *rules);

#endif
