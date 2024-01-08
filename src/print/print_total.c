/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_total.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:11:44 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:11:44 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_total(blkcnt_t total, bool l)
{
	if (!l)
		return ;
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd(total, 1);
	write(1, "\n", 1);
}
