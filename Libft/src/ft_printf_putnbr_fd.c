/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 13:09:46 by echapus           #+#    #+#             */
/*   Updated: 2022/11/18 09:56:39 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putnbr_fd(int nbr, int fd, int *count)
{
	unsigned int	x;
	char			c;

	if (nbr < 0)
	{
		write(fd, "-", 1);
		*count += 1;
		x = -nbr;
	}
	else
		x = nbr;
	while (x >= 10)
	{
		ft_putnbr_fd(x / 10, fd, count);
		x %= 10;
	}
	c = x + '0';
	write(fd, &c, 1);
	*count += 1;
}

int	ft_nbr_fd(int nbr, int fd)
{
	int	count;

	count = 0;
	ft_putnbr_fd(nbr, fd, &count);
	return (count);
}

static void	ft_putunbr_fd(unsigned int nbr, int fd, int *count)
{
	char	c;

	while (nbr >= 10)
	{
		ft_putunbr_fd(nbr / 10, fd, count);
		nbr %= 10;
	}
	c = nbr + '0';
	write(fd, &c, 1);
	*count += 1;
}

int	ft_unbr_fd(unsigned int nbr, int fd)
{
	int	count;

	count = 0;
	ft_putunbr_fd(nbr, fd, &count);
	return (count);
}
