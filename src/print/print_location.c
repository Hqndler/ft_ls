/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_location.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:11:27 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:33:39 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_location(t_data data, char *cwd)
{
	int	i;

	if (!data.recursive && !data.arg_dir)
		return ;
	i = 0;
	if (!data.arg_dir)
		while (cwd[i] && data.cwd[i] && cwd[i] == data.cwd[i])
			++i;
	if (!data.arg_dir)
		write(1, ".", 1);
	ft_putstr_fd(&(cwd[i]), 1);
	write(1, ":\n", 2);
}
