/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:16:40 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/12 14:34:59 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philosopher
{
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	struct s_state	*state;
	long			last_meal_time;
	int				id;
	int				meals_eaten;
}					t_philo;

typedef struct s_state
{
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	long			start_time;
	int				stop_simulation;
	int				required_meals;
	int				time_to_sleep;
	int				time_to_die;
	int				time_to_eat;
	int				num_philo;
}					t_state;

long				get_time_in_ms(void);
void				init_state(t_state *state, int argc, char **argv);
void				init_philo(t_philo *philo, t_state *state);
void				*philo_lifecycle(void *arg);
void				start_simulation(t_philo *philo, t_state *state);
void				cleanup(t_philo *philo, t_state *state);
void				*philo_lifecycle(void *arg);
int					ft_atoi(const char *str);
void				syntax(char **av);
#endif
