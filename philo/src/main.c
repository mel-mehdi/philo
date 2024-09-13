/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 02:09:51 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/06 18:29:19 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

void	free_philo(t_data *data)
{
	t_philo	*philo;
	t_philo	*tmp;
	int		i;

	philo = data->philo;
	i = 0;
	while (i < data->philo_nbr)
	{
		tmp = philo->next;
		free(philo);
		philo = tmp;
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (check_args(&data, av, ac) == -1)
			return (1);
		init_philo(&data);
		start_routine(&data);
		free_philo(&data);
	}
	else
		print_error(0);
}
