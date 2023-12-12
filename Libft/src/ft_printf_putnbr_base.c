/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:26:46 by echapus           #+#    #+#             */
/*   Updated: 2022/11/17 15:08:10 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_base_loop(unsigned int nbr, int fd, char *base, int *count)
{
	if (nbr >= 16)
	{
		ft_base_loop(nbr / 16, fd, base, count);
		nbr %= 16;
	}
	ft_printf_putchar_fd(base[nbr], fd);
	*count += 1;
}

int	ft_putnbr_base_fd(unsigned int nbr, int fd, char c)
{
	char	*base_up;
	char	*base_lo;
	int		count;

	count = 0;
	base_lo = "0123456789abcdef";
	base_up = "0123456789ABCDEF";
	if (c == 'x')
		ft_base_loop(nbr, fd, base_lo, &count);
	else
		ft_base_loop(nbr, fd, base_up, &count);
	return (count);
}
