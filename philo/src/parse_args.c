/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 16:21:43 by melmehdi          #+#    #+#             */
/*   Updated: 2024/09/12 16:20:20 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	print_error(int flag)
{
	if (flag == 0)
		ft_putstr_fd("Error: invalid arguments number", 2, '\n');
	else if (flag == 1)
		ft_putstr_fd("Error: malloc failed", 2, '\n');
	else if (flag == 2)
		ft_putstr_fd("Error: invalid arguments", 2, '\n');
	else if (flag == 3)
		ft_putstr_fd("Error: invalid int", 2, '\n');
	return (-1);
}

void	init_data(t_data *data, int ac, int args[4])
{
	data->philo_nbr = args[0];
	data->d_time = args[1];
	data->e_time = args[2];
	data->s_time = args[3];
	data->ac = ac;
	if (ac == 6)
		data->meals_nb = args[4];
}

int	check_valid_element(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+' && (i == 0 && str[i + 1]))
		{
			i++;
			continue ;
		}
		else if ((str[i] == '+') \
		&& (i != 0 || !str[i + 1]))
			return (0);
		if ((str[i] < '0' || str[i] > '9'))
			return (0);
		i++;
	}
	if (!i)
		return (0);
	return (1);
}

int	check_args(t_data *data, char **av, int ac)
{
	int		args[4];
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (av[i])
	{
		if (!check_valid_element(av[i]))
			return (print_error(2));
		else
		{
			args[j] = ft_atoi(av[i]);
			if (args[j] == -1)
				return (print_error(3));
			j++;
		}
		i++;
	}
	if (!i)
		return (print_error(2));
	init_data(data, ac, args);
	return (0);
}
