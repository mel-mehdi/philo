/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_lifecycle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:56:01 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/12 09:57:05 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_status(t_philo *philo, const char *status)
{
	t_state	*state;

	state = philo->state;
	pthread_mutex_lock(&state->print_lock);
	printf("%ld %d %s\n", get_time_in_ms() - state->start_time, \
	philo->id, status);
	pthread_mutex_unlock(&state->print_lock);
}

void	pick_up_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_status(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	t_state	*state;

	state = philo->state;
	print_status(philo, "is eating");
	philo->last_meal_time = get_time_in_ms();
	philo->meals_eaten++;
	usleep(state->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

void	sleep_and_think(t_philo *philo)
{
	t_state	*state;

	state = philo->state;
	print_status(philo, "is sleeping");
	usleep(state->time_to_sleep * 1000);
	print_status(philo, "is thinking");
}

void	*philo_lifecycle(void *arg)
{
	t_philo	*philo;
	t_state	*state;

	philo = (t_philo *)arg;
	state = philo->state;
	while (!state->stop_simulation)
	{
		sleep_and_think(philo);
		pick_up_forks(philo);
		eat(philo);
		if (state->required_meals != -1 && philo->meals_eaten \
		>= state->required_meals)
			break ;
	}
	return (NULL);
}
