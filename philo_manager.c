/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:58:21 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/12 14:20:43 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_philo_threads(pthread_t *threads, t_philo *philo, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->num_philo)
	{
		pthread_create(&threads[i], NULL, philo_lifecycle, \
		&philo[i]);
		i++;
	}
}

void	monitor_philo(t_philo *philo, t_state *state)
{
	int	i;

	while (!state->stop_simulation)
	{
		i = 0;
		while (i < state->num_philo)
		{
			if (get_time_in_ms() - philo[i].last_meal_time > \
			state->time_to_die)
			{
				pthread_mutex_lock(&state->print_lock);
				printf("%ld %d died\n", get_time_in_ms() - \
				state->start_time, philo[i].id);
				pthread_mutex_unlock(&state->print_lock);
				state->stop_simulation = 1;
				state->num_philo -= 1;
					// exit(0)
				break ;
			}
			i++;
		}
	}
}

void	join_philo_threads(pthread_t *threads, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->num_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

void	start_simulation(t_philo *philo, t_state *state)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * state->num_philo);
	if (!threads)
		return ;
	create_philo_threads(threads, philo, state);
	monitor_philo(philo, state);
	join_philo_threads(threads, state);
	free(threads);
}

void	cleanup(t_philo *philo, t_state *state)
{
	int	i;

	i = 0;
	while (i < state->num_philo)
	{
		pthread_mutex_destroy(&state->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&state->print_lock);
	free(state->forks);
	free(philo);
}
