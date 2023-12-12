/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:59:41 by echapus           #+#    #+#             */
/*   Updated: 2022/11/17 15:52:53 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_write_type(char c, va_list arg)
{
	if (c == 'c')
		return (ft_printf_putchar_fd(va_arg(arg, int), 1));
	if (c == 's')
		return (ft_printf_putstr_fd(va_arg(arg, char *), 1));
	if (c == 'p')
		return (ft_pointer_fd(va_arg(arg, long long unsigned int), 1));
	if (c == 'd' || c == 'i')
		return (ft_nbr_fd(va_arg(arg, int), 1));
	if (c == 'u')
		return (ft_unbr_fd(va_arg(arg, unsigned int), 1));
	if (c == 'x' || c == 'X')
		return (ft_putnbr_base_fd(va_arg(arg, unsigned int), 1, c));
	return (ft_printf_putchar_fd('%', 1));
}
