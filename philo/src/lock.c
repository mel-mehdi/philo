/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lock.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 15:20:52 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/04 11:40:41 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	lock_fork(t_philo *philo, int flag)
{
	if (flag == 0)
	{
		if (philo->l_fork != NULL && philo->id % 2 == 0)
			pthread_mutex_lock(philo->l_fork);
		else if (philo->r_fork != NULL)
			pthread_mutex_lock(philo->r_fork);
	}
	else if (flag == 1)
	{
		if (philo->r_fork != NULL && philo->id % 2 == 0)
			pthread_mutex_lock(philo->r_fork);
		else if (philo->l_fork != NULL)
			pthread_mutex_lock(philo->l_fork);
	}
}

void	unlock_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
	}
}
