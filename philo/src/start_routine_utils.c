/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 18:40:04 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/13 10:10:04 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	check_death(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->s_monitor));
	i = 0;
	if (data->finish == true)
		i = 1;
	pthread_mutex_unlock(&(data->s_monitor));
	return (i);
}

void	*death(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&(data->death));
	data->finish = true;
	pthread_mutex_unlock(&(data->death));
	pthread_mutex_unlock(&(data->s_monitor));
	print_action(philo, 3, (ft_get_time_ms() - (data->starting_time)));
	ft_join(data);
	destroy(data);
	return (NULL);
}

int	ft_get_time_ms(void)
{
	int				i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (i);
}

void	ft_join(t_data *data)
{
	t_philo			*tmp;
	int				i;

	tmp = data->philo;
	i = 0;
	while (i < data->philo_nbr)
	{
		pthread_join(tmp->trd, NULL);
		tmp = tmp->next;
		i++;
	}
}

void	ft_usleep(int i, t_data *data)
{
	int	j;

	j = ft_get_time_ms() - (data->starting_time);
	while (ft_get_time_ms() - (data->starting_time) - j < i)
	{
		if (data->flag == 0)
			usleep(200);
		else
			break;
	}
}
