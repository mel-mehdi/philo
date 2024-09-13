/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 13:33:47 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/27 14:04:52 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo	*new_philo(t_data *data, pthread_mutex_t *l_fork, \
pthread_mutex_t *r_fork, int id)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->l_fork = l_fork;
	philo->r_fork = r_fork;
	philo->nbr_eaten_meals = 0;
	philo->last_meal = 0;
	philo->id = id;
	philo->next = NULL;
	philo->data = data;
	return (philo);
}

pthread_mutex_t	*create_forks(int nbr)
{
	pthread_mutex_t	*forks;
	int				i;

	forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * nbr);
	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&(forks[i]), NULL);
		i++;
	}
	return (forks);
}

void	init(t_data *data)
{
	data->starting_time = ft_get_time_ms();
	data->forks = create_forks(data->philo_nbr);
	data->start_monitoring = false;
	data->flag = 0;
	data->finish = false;
	data->philo = NULL;
	data->finish_eating = 0;
	pthread_mutex_init(&(data->death), NULL);
	pthread_mutex_init(&(data->death2), NULL);
	pthread_mutex_init(&(data->s_monitor), NULL);
}

void	set_forks(t_philo *philo, t_data *data, int flag, int i)
{
	if (flag == 0)
	{
		philo->next = new_philo(data, &(data->forks)[i + 1], \
		&(data->forks)[i], i + 1);
	}
	else if (flag == 1)
	{
		philo->next = new_philo(data, \
		&(data->forks)[data->philo_nbr - 1], \
		&(data->forks)[0], data->philo_nbr);
	}
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	init(data);
	i = 0;
	data->philo = check_one_philo(data, &i);
	while (i < data->philo_nbr && data->philo_nbr != 0)
	{
		if (data->philo == NULL)
		{
			data->philo = new_philo(data, &(data->forks)[i], \
			&(data->forks)[i + 1], 1);
			philo = data->philo;
			i++;
		}
		if (i != data->philo_nbr - 1)
			set_forks(philo, data, 0, i);
		else
			set_forks(philo, data, 1, i);
		philo = philo->next;
		i++;
	}
}
