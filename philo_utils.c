/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:17:27 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/12 14:34:34 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_in_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_state(t_state *state, int argc, char **argv)
{
	int	i;

	state->num_philo = ft_atoi(argv[1]);
	state->time_to_die = ft_atoi(argv[2]);
	state->time_to_eat = ft_atoi(argv[3]);
	state->time_to_sleep = ft_atoi(argv[4]);
	if(!state->num_philo)
		exit(0);
	if (argc == 6)
		state->required_meals = ft_atoi(argv[5]);
	else
		state->required_meals = -1;
	state->forks = malloc(sizeof(pthread_mutex_t) * state->num_philo);
	i = 0;
	while (i < state->num_philo)
	{
		pthread_mutex_init(&state->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&state->print_lock, NULL);
	state->stop_simulation = 0;
	state->start_time = get_time_in_ms();
}

void	init_philo(t_philo *philo, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].meals_eaten = 0;
		philo[i].last_meal_time = state->start_time;
		philo[i].left_fork = &state->forks[i];
		philo[i].right_fork = &state->forks[(i + 1)
			% state->num_philo];
		philo[i].state = state;
		i++;
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	neg;
	int	res;

	i = 0;
	neg = 1;
	res = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (str[i] - '0') + (res * 10);
		i++;
	}
	return (res * neg);
}
