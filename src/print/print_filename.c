/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:11:52 by echapus           #+#    #+#             */
/*   Updated: 2024/04/04 19:14:13 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_filename(char *name, bool l, bool a, t_data data)
{
	char	buffer[4096];
	char	tmp[4096];
	int		ret;

	if (name[0] == '.' && !a)
		return ;
	if (!l)
		return (ft_putstr_fd(name, 1), ft_putstr_fd("  ", 1));
	ft_putstr_fd(name, 1);
	ft_bzero(tmp, 4096);
	ft_strlcat(tmp, data.cwd, 4096);
	ft_strlcat(tmp, "/", 4096);
	ft_strlcat(tmp, name, 4096);
	ret = readlink(tmp, buffer, 4095);
	if (ret != -1)
	{
		buffer[ret] = 0;
		ft_putstr_fd(" -> ", 1);
		ft_putendl_fd(buffer, 1);
	}
	else
		ft_putendl_fd("", 1);
}
