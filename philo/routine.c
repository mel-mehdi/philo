/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 11:17:22 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/20 12:10:23 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print(philo, "has taken a right fork");
	if (philo->philos_num == 1)
	{
		ft_usleep(philo->phil_death_time);
		pthread_mutex_unlock(philo->r_fork);
		return ;
	}
	pthread_mutex_lock(philo->l_fork);
	print(philo, "has taken a left fork");
	philo->eating = 1;
	print(philo, "is eating");
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_time();
	philo->eating_count++;
	print(philo, "is done eating");
	pthread_mutex_unlock(philo->meal_lock);
	ft_usleep(philo->phil_eat_time);
	philo->eating = 0;
	print(philo, "put the forks back");
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	sleeping(t_philo *philo)
{
	print(philo, "is sleeping");
	ft_usleep(philo->phil_sleep_time);
}

void	thinking(t_philo *philo)
{
	print(philo, "is thinking");
}

int	dead_monitor(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_life(void *philo)
{
	t_philo	*p;

	p = (t_philo *)philo;
	if (p->id % 2 == 0)
		ft_usleep(1);
	while (!dead_monitor(p))
	{
		eating(p);
		sleeping(p);
		thinking(p);
	}
	return (NULL);
}
