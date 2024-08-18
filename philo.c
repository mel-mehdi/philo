/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 18:52:28 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/17 11:27:13 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_state	state;

	if (argc != 5 && argc != 6)
	{
		printf("Usage: %s number_of_philo time_to_die time_to_eat \
        time_to_sleep[number_of_times_each_philo_must_eat]\n ", \
		argv[0]);
		return (1);
	}
	syntax(argv);
	init_state(&state, argc, argv);
	philo = malloc(sizeof(t_philo) * state.num_philo);
	if(!philo)
		return (1);
	init_philo(philo, &state);
	start_simulation(philo, &state);
	cleanup(philo, &state);
	return (0);
}
