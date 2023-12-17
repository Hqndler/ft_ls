/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 23:35:23 by echapus           #+#    #+#             */
/*   Updated: 2022/11/11 14:03:00 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(long n, int fd)
{
	unsigned long	x;
	char			c;

	if (n < 0)
	{
		write(fd, "-", 1);
		x = -n;
	}
	else
		x = n;
	while (x >= 10)
	{
		ft_putnbr_fd(x / 10, fd);
		x %= 10;
	}
	c = x + '0';
	write(fd, &c, 1);
}
