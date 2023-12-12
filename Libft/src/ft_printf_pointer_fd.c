/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 14:25:35 by echapus           #+#    #+#             */
/*   Updated: 2022/11/18 09:54:50 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void
	ft_pointer_loop(long long unsigned int nbr, int fd, char *base, int *count)
{
	if (nbr >= 16)
	{
		ft_pointer_loop(nbr / 16, fd, base, count);
		nbr %= 16;
	}
	ft_printf_putchar_fd(base[nbr], fd);
	*count += 1;
}

int	ft_pointer_fd(long long unsigned int ptr, int fd)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	if (ptr == 0)
	{
		ft_printf_putstr_fd("(nil)", 1);
		return (5);
	}
	count = ft_printf_putstr_fd("0x", fd);
	ft_pointer_loop(ptr, fd, base, &count);
	return (count);
}
