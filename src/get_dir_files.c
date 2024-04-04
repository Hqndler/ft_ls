/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:18:52 by echapus           #+#    #+#             */
/*   Updated: 2024/04/04 18:59:07 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	size_len(long long bytes)
{
	int	size;

	size = 1;
	while (bytes >= 10)
	{
		++size;
		bytes /= 10;
	}
	return (size);
}

static int	open_stat(t_list *list, char *cwd)
{
	t_list	*actual;
	char	path[PATH_MAX];

	actual = list->prev;
	ft_memset(path, 0, PATH_MAX);
	ft_strlcat(path, cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, actual->path, PATH_MAX);
	if (!stat(path, &(actual->file_stat)))
		return (1);
	else
		perror("Error while getting file stat");
	return (0);
}

static void	get_bytes(t_list *list, t_data *data)
{
	t_list	*actual;
	int		slen;

	actual = list->prev;
	if (actual->path[0] == '.' && !data->a)
		return ;
	data->total_block_count += actual->file_stat.st_blocks;
	slen = size_len(actual->file_stat.st_size);
	actual->spacesize = slen;
	if (slen > data->bytespace)
		data->bytespace = slen;
	slen = size_len(actual->file_stat.st_nlink);
	actual->spacelink = slen;
	if (slen > data->linkspace)
		data->linkspace = slen;
	if (S_ISDIR(actual->file_stat.st_mode) && \
		(ft_strcmp(actual->path, ".") != 0 && \
		ft_strcmp(actual->path, "..") != 0))
		actual->dir = true;
}

int	get_dir_files(char *cwd, t_data *data, t_list **list)
{
	DIR				*dir;
	struct dirent	*fileread;

	dir = NULL;
	dir = opendir(cwd);
	if (!dir)
		return (perror("opendir"), 0);
	fileread = NULL;
	while (1)
	{
		fileread = readdir(dir);
		if (!fileread)
			break ;
		if (!list_append(list, fileread->d_name) || !open_stat(*list, cwd))
			return (closedir(dir), free_list(list), 0);
		get_bytes(*list, data);
	}
	closedir(dir);
	return (1);
}
