/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 12:28:33 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/20 12:09:58 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	exit_error(char *s)
{
	printf("%s\n", s);
	return (false);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	error(void)
{
	printf("\033[1;97mInvalid Number of Arguments\033[1;91m\n");
	return (0);
}

void	init_prog(t_philo *philos, t_prog *prog)
{
	prog->death_flag = 0;
	prog->philo = philos;
	pthread_mutex_init(&prog->dead_lock, NULL);
	pthread_mutex_init(&prog->meal_lock, NULL);
	pthread_mutex_init(&prog->write_lock, NULL);
}

int	main(int ac, char **av)
{
	t_args			args;
	t_philo			philos[PHILOS_MAX];
	t_prog			prog;
	pthread_mutex_t	forks[PHILOS_MAX];

	if (!(ac == 5 || ac == 6))
		return (error());
	if (!init_args(&args, av, ac))
		return (1);
	init_forks(forks, _atoi(av[1]));
	if (!init_philos(&args, philos, &prog, forks))
		return (1);
	if (!init_thread(philos, forks, &prog))
		return (1);
	destroy_all(NULL, &prog, forks, philos);
}
