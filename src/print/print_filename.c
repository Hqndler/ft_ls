/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:11:52 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:12:14 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_filename(char *name, bool l, bool a)
{
	if (name[0] == '.' && !a)
		return ;
	if (l)
		return (ft_putendl_fd(name, 1));
	ft_putstr_fd(name, 1);
	ft_putstr_fd("  ", 1);
}
