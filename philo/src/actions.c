/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:42:49 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/12 16:20:32 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo	*check_one_philo(t_data *data, int *i)
{
	t_philo	*philo;

	if (data->philo_nbr == 1)
	{
		philo = new_philo(data, &(data->forks)[0], NULL, 1);
		(*i)++;
		return (philo);
	}
	return (NULL);
}

int	eating(t_philo *philo)
{
	if (philo->l_fork == NULL)
		return (1);
	lock_fork(philo, 0);
	print_action(philo, 0, (ft_get_time_ms() - (philo->data->starting_time)));
	if (philo->r_fork == NULL)
		return (1);
	lock_fork(philo, 1);
	print_action(philo, 0, (ft_get_time_ms() - (philo->data->starting_time)));
	print_action(philo, 1, (ft_get_time_ms() - (philo->data->starting_time)));
	pthread_mutex_lock(&(philo->data->s_monitor));
	philo->nbr_eaten_meals++;
	if (philo->data->ac == 6 && philo->nbr_eaten_meals == philo->data->meals_nb)
		philo->data->finish_eating++;
	pthread_mutex_unlock(&(philo->data->s_monitor));
	pthread_mutex_lock(&(philo->data->s_monitor));
	philo->last_meal = ft_get_time_ms() - (philo->data->starting_time);
	pthread_mutex_unlock(&(philo->data->s_monitor));
	ft_usleep(philo->data->e_time, philo->data);
	unlock_fork(philo);
	return (0);
}

void	sleeping(t_philo *philo)
{
	print_action(philo, 2, (ft_get_time_ms() - (philo->data->starting_time)));
	ft_usleep(philo->data->s_time, philo->data);
}

void	destroy(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	philo = data->philo;
	while (i < data->philo_nbr)
	{
		pthread_mutex_destroy(data->forks + i);
		i++;
	}
	free(data->forks);
	pthread_mutex_destroy(&(data->s_monitor));
	pthread_mutex_destroy(&(data->death));
}
