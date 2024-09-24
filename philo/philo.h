/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:00:00 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/23 09:43:39 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <semaphore.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <string.h>
# include <time.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/mman.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/time.h>

# define PHILOS_MAX	300

// struct of philosophers
typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			phil_death_time;
	size_t			phil_eat_time;
	size_t			phil_sleep_time;
	size_t			start_time;
	int				eat_times;
	int				eating_count;
	int				philos_num;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}	t_philo;

typedef struct s_prog
{
	int				death_flag;
	t_philo			*philo;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
}	t_prog;

typedef struct s_args
{
	int		philos_num;
	size_t	time_to_die;
	size_t	time_to_eat;
	size_t	time_to_sleep;
	size_t	philos_eat_times;
}	t_args;

// philo.c functions
bool	exit_error(char *s);
int		error(void);
void	init_prog(t_philo *philos, t_prog *prog);

// utils.c functions
long		_atoi(char *s);
int		_isdigit(char c);
bool	is_digit(char **av);
long	get_time(void);
void	print(t_philo *philo, char *s);
int		ft_usleep(size_t milliseconds, t_philo *philo);
// int		ft_usleep(size_t milliseconds);

// init functions
bool	init_args(t_args *args, char **av, int ac);
bool	init_philos(t_args *args, t_philo *philos,
			t_prog *prog, pthread_mutex_t *forks);
void	init_forks(pthread_mutex_t *forks, int philo_num);
int		init_thread(t_philo *philos, pthread_mutex_t *forks, t_prog *prog);
void	helper(int i, t_philo *philos, t_args *args, pthread_mutex_t *forks);
void	init_prog(t_philo *philos, t_prog *prog);
// routine functions

void	eating(t_philo *philo);
void	sleeping(t_philo *philo);
void	thinking(t_philo *philo);
int		dead_monitor(t_philo *philo);
void	*philo_life(void *philo);
void	takeforks(t_philo *philo);

// monitor functions
void	*monitor(void *pointer);
int		eat_times(t_philo *philo);
int		check_death(t_philo *philos);
int		philo_dead(t_philo *philo, size_t dead_time);
int		destroy_all(char *mssg, t_prog *prog,
			pthread_mutex_t *forks, t_philo *philo);

#endif // PHILO_H
