/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 12:58:11 by echapus           #+#    #+#             */
/*   Updated: 2022/11/18 09:56:17 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_printf_putstr_fd(char *str, int fd)
{
	int	count;

	if (!str)
		str = "(null)";
	count = ft_strlen(str);
	write(fd, str, count);
	return (count);
}
