/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:14:03 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:33:27 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*first_pointer(t_list *list, t_data data)
{
	if (data.r)
		return (list->prev);
	return (list);
}
	// return ((data.r) ? list->prev : list);

static t_list	*following_pointer(t_list *list, t_data data)
{
	if (data.r)
		return (list->prev);
	return (list->next);
}
	// return ((data.r) ? list->prev : list->next);

int	next_dir(t_data data, t_list *list, size_t len)
{
	t_list	*tmp;
	char	dir[PATH_MAX];

	tmp = first_pointer(list, data);
	ft_strlcpy(dir, data.dir, PATH_MAX);
	while (len--)
	{
		if ((data.a && tmp->dir) || \
			(!data.a && tmp->path[0] != '.' && tmp->dir))
		{
			ft_putendl_fd("", 1);
			ft_strlcat(data.dir, "/", PATH_MAX);
			ft_strlcat(data.dir, tmp->path, PATH_MAX);
			if (ft_ls_recursive(data, data.dir))
				return (free_list(&list), 0);
			ft_strlcpy(data.dir, dir, PATH_MAX);
		}
		tmp = following_pointer(tmp, data);
	}
	return (1);
}

int	ft_ls_recursive(t_data data, char *cwd)
{
	t_list	*list;
	size_t	len;

	list = NULL;
	data.total_block_count = 0;
	data.bytespace = 0;
	data.linkspace = 0;
	if (!get_dir_files(cwd, &data, &list) || \
		!sort_list_name(&list, data.t))
		return (free_list(&list), 0);
	len = len_list(list);
	print_location(data, cwd);
	ft_ls(data, list, len);
	if (!data.recursive)
		return (free_list(&list), 0);
	if (!next_dir(data, list, len))
		return (1);
	return (free_list(&list), 0);
}

int	ft_ls(t_data data, t_list *list, size_t len)
{
	t_list	*tmp;

	print_total(data.total_block_count / 2, data.l);
	tmp = first_pointer(list, data);
	while (len--)
	{
		if (!data.a && tmp->path[0] == '.')
		{
			tmp = following_pointer(tmp, data);
			continue ;
		}
		if (data.l)
		{
			print_permission_link(tmp, data);
			print_owner_group(list);
			print_size(tmp, data);
			print_time(tmp->file_stat.st_mtime, data);
		}
		print_filename(tmp->path, data.l, data.a);
		tmp = following_pointer(tmp, data);
	}
	if (!data.l)
		ft_putendl_fd("", 1);
	return (1);
}
