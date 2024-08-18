/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 10:10:39 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/12 10:53:32 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_white_space(int c)
{
	return ((c == 32) || (c >= 9 && c <= 13));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	syntax(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (ft_is_white_space(av[i][j]))
			j++;
		// if (av[i][j] == '+' || av[i][j] == '-')
		// 	j++;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
			{
				exit(1);
			}
		}
		i++;
	}
}
