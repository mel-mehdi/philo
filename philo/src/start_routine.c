/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 12:43:51 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/13 10:11:19 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	print_died_philo(t_philo *philo, int time)
{
	if (philo->data->flag == 0)
	{
		pthread_mutex_lock(&(philo->data->death2));
		philo->data->flag = 1;
		pthread_mutex_unlock(&(philo->data->death2));
		printf("%d %d died\n", time, philo->id);
	}
	pthread_mutex_unlock(&(philo->data->death));
	pthread_mutex_unlock(&(philo->data->s_monitor));
}

int	print_action(t_philo *philo, int action, int time)
{
	pthread_mutex_lock(&(philo->data->s_monitor));
	pthread_mutex_lock(&(philo->data->death));
	if (philo->data->finish == true && \
	philo->data->finish_eating != philo->data->philo_nbr)
	{
		print_died_philo(philo, time);
		return (1);
	}
	if (action == 0)
		printf("%d %d has taken a fork\n", time, philo->id);
	else if (action == 1)
		printf("%d %d is eating\n", time, philo->id);
	else if (action == 2)
		printf("%d %d is sleeping\n", time, philo->id);
	else if (action == 3)
		printf("%d %d is thinking\n", time, philo->id);
	pthread_mutex_unlock(&(philo->data->death));
	pthread_mutex_unlock(&(philo->data->s_monitor));
	return (0);
}

void	*monitoring(void *data1)
{
	t_philo	*philo;
	t_data	*data;
	int		i;

	data = (t_data *)data1;
	philo = data->philo;
	while (philo != 0)
	{
		pthread_mutex_lock(&(data->s_monitor));
		i = (ft_get_time_ms() \
		- (philo->data->starting_time)) - (philo->last_meal);
		pthread_mutex_unlock(&(data->s_monitor));
		pthread_mutex_lock(&(data->s_monitor));
		if (i >= data->d_time || data->finish_eating == data->philo_nbr)
			return (death(data, philo));
		pthread_mutex_unlock(&(data->s_monitor));
		if (philo->id == data->philo_nbr)
			philo = data->philo;
		else
			philo = philo->next ;
		usleep(100);
	}
	return (NULL);
}

void	*routine(void *philo1)
{
	t_philo	*philo;

	philo = (t_philo *)philo1;
	while (1)
	{
		if (check_death(philo->data) == 1)
			return (NULL);
		else
		{
			if (philo->id % 2 != 0)
				usleep(200);
			if (eating(philo) == 1)
				return (NULL);
			sleeping(philo);
			usleep(200);
		}
	}
	return (NULL);
}

void	start_routine(t_data *data)
{
	t_philo			*philo;
	pthread_t		tr;

	philo = data->philo;
	while (philo != 0)
	{
		pthread_create(&(philo->trd), NULL, &routine, philo);
		philo = philo->next;
	}
	pthread_create(&tr, NULL, &monitoring, data);
	pthread_join(tr, NULL);
}
