/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:10:05 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/07 09:47:23 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include "./utils/libft/libft.h"

typedef struct s_philo
{
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*next;
	struct s_data	*data;
	pthread_t		trd;
	int				nbr_eaten_meals;
	int				last_meal;
	int				id;
}					t_philo;

typedef struct s_data
{
	pthread_mutex_t	s_monitor;
	pthread_mutex_t	death2;
	pthread_mutex_t	*forks;
	pthread_mutex_t	death;
	t_philo			*philo;
	bool			start_monitoring;
	bool			finish;
	int				starting_time;
	int				finish_eating;
	int				philo_nbr;
	int				meals_nb;
	int				e_time;
	int				d_time;
	int				s_time;
	int				args[4];
	int				flag;
	int				ac;
}					t_data;

t_philo			*new_philo(t_data *data, pthread_mutex_t *r_fork, \
pthread_mutex_t *l_fork, int id);
t_philo			*check_one_philo(t_data *data, int *i);
void			init_philo(t_data *data);
void			start_routine(t_data *data);
void			*routine(void *philo);
int				print_action(t_philo *philo, int action, int time);
void			ft_usleep(int i, t_data *data);
void			ft_join(t_data *data);
void			*death(t_data *data, t_philo *philo);
void			sleeping(t_philo *philo);
void			destroy(t_data *data);
void			lock_fork(t_philo *philo, int flag);
void			unlock_fork(t_philo *philo);
int				check_args(t_data *data, char **av, int ac);
int				print_error(int flag);
int				ft_get_time_ms(void);
int				ft_get_time_ms(void);
int				check_death(t_data *data);
int				eating(t_philo *philo);

#endif
