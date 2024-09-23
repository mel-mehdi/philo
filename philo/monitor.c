/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:21:13 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/20 10:27:47 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_all(char *mssg, t_prog *prog,
				pthread_mutex_t *forks, t_philo *philo)
{
	int	i;

	i = -1;
	if (mssg)
		printf("%s\n", mssg);
	pthread_mutex_destroy(&prog->meal_lock);
	pthread_mutex_destroy(&prog->dead_lock);
	pthread_mutex_destroy(&prog->write_lock);
	while (++i < philo[0].philos_num)
		pthread_mutex_destroy(&forks[i]);
	return (1);
}

int	philo_dead(t_philo *philo, size_t dead_time)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_time() - philo->last_meal >= dead_time && philo->eating == 0)
		return ((pthread_mutex_unlock(philo->meal_lock)), 1);
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_death(t_philo *philos)
{
	int	i;

	i = -1;
	while (philos && ++i < philos[0].philos_num)
	{
		if (philo_dead(&philos[i], philos[i].phil_death_time) == 1)
		{
			print(&philos[i], "died");
			pthread_mutex_lock(philos->dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos->dead_lock);
			return (1);
		}
	}
	return (0);
}

int	eat_times(t_philo *philo)
{
	int	i;
	int	finished;

	i = -1;
	finished = 0;
	while (philo[0].eat_times != -1 && ++i < philo[0].philos_num)
	{
		pthread_mutex_lock(philo[i].meal_lock);
		if (philo[i].eating_count >= philo[i].eat_times)
			finished++;
		pthread_mutex_unlock(philo[i].meal_lock);
	}
	if (finished == philo[0].philos_num)
	{
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_death(philos) == 1 || eat_times(philos) == 1)
			break ;
	return (pointer);
}
