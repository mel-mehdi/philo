/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 09:11:22 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/25 12:55:13 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print(t_philo *philo, char *s)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_time() - philo->start_time;
	if (!dead_monitor(philo))
		printf("%ld %d %s\n", time, philo->id, s);
	pthread_mutex_unlock(philo->write_lock);
}

int	_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	_atoi(char *s)
{
	long	sign;
	long	res;
	long	i;

	sign = 1;
	res = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (_isdigit(s[i]))
	{
		res = res * 10 + s[i] - '0';
		i++;
	}
	return (res * sign);
}

bool	is_digit(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!_isdigit(av[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}
