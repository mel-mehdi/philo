/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melmehdi <melmehdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:55:59 by melmehdi          #+#    #+#             */
/*   Updated: 2024/08/27 14:04:52 by melmehdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd, char end_l)
{
	int	i;

	i = ft_strlen(s);
	write(fd, s, i);
	write (fd, &end_l, 1);
}
