#include "ft_ls.h"

static int	size_len(long long bytes){
	int	size;

	size = 1;
	while (bytes >= 10){
		++size;
		bytes /= 10;
	}
	return size;
}

static int	open_stat(t_list *list, char *cwd){
	t_list	*actual;
	char	path[PATH_MAX];

	actual = list->prev;
	ft_memset(path, 0, PATH_MAX);
	ft_strlcat(path, cwd, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, actual->path, PATH_MAX);
	if (!stat(path, &(actual->file_stat)))
		return 1;
	else
		perror("Error while getting file stat");
	return 0;
}

static void	get_bytes(t_list *list, t_data *data){
	t_list	*actual;
	int		slen;

	actual = list->prev;
	data->total_block_count += actual->file_stat.st_blocks;
	slen = size_len(actual->file_stat.st_size);
	actual->spacesize = slen;
	if (slen > data->bytespace)
		data->bytespace = slen;
	slen = size_len(actual->file_stat.st_nlink);
	actual->spacelink = slen;
	if (slen > data->linkspace)
		data->linkspace = slen;
}

int	get_dir_files(char *cwd, t_data *data, t_list **list)
{
	DIR	*dir;

	dir = NULL;
	dir = opendir(cwd);
	// printf("_%s_\n", cwd);
	if (!dir)
		return perror("opendir"), 1;
	struct dirent	*fileread = NULL;
	while (1)
	{
		fileread = readdir(dir);
		if (!fileread)
			break;
		if (!list_append(list, fileread->d_name) || !open_stat(*list, cwd))
			return closedir(dir), free_list(list);
		get_bytes(*list, data);
	}
	closedir(dir);
	return (0);
}