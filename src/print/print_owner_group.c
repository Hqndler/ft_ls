/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_owner_group.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:12:56 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:13:46 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_owner_group(t_list *list)
{
	t_list			*actual;
	struct passwd	*owner_info;
	struct group	*group_info;

	actual = list->prev;
	owner_info = getpwuid(actual->file_stat.st_uid);
	group_info = getgrgid(actual->file_stat.st_gid);
	if (!owner_info || !group_info)
	{
		perror("Error in getpwuid or getgrgid");
		return ;
	}
	ft_putstr_fd(owner_info->pw_name, 1);
	write(1, " ", 1);
	ft_putstr_fd(group_info->gr_name, 1);
	write(1, " ", 1);
}
