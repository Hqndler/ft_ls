#include "ft_ls.h"

static t_list	*first_pointer(t_list *list, t_data data){
	return ((data.r) ? list->prev : list);
}

static t_list	*following_pointer(t_list *list, t_data data){
	return ((data.r) ? list->prev : list->next);
}

int	print_location(t_data data, char *cwd)
{
	int	i;
	if (!data.R)
		return (1);
	i = 0;
	while (cwd[i] == data.cwd[i])
		++i;
	write(1, ".", 1);
	ft_putstr_fd(&(cwd[i]), 1);
	write(1, ":\n", 2);
	return (1);
}

int	ft_ls_recursive(t_data data, char *cwd)
{
	t_list	*list;
	t_list	*tmp;
	size_t	len;

	list = NULL;
	if (get_dir_files(cwd, &data, &list))
		return (1);
	if (print_location(data, cwd) && ft_ls(data, list, cwd))
		return (1);
	if (!data.R)
		return free_list(&list), 0;
	tmp = list;
	len = len_list(list);
	while (len--)
	{
		if ((data.a && S_ISDIR(tmp->file_stat.st_mode)) || (!data.a && \
			tmp->path[0] != '.' && S_ISDIR(tmp->file_stat.st_mode)))
		{
			ft_strlcat(data.dir, "/", PATH_MAX);
			ft_strlcat(data.dir, tmp->path, PATH_MAX);
			printf("new path : _%s_\n", data.dir);
			if (ft_ls_recursive(data, data.dir))
				return free_list(&list), (1);
		}
		tmp = tmp->next;
	}
	return free_list(&list), (0);
}

int	ft_ls(t_data data, t_list *list, char *cwd)
{
	t_list	*tmp;
	size_t	len;

	(void)cwd;
	print_total(data.total_block_count / 2, data.l);
	if (!sort_list_name(&list, ALPHA))
		return ft_putstr_fd("malloc error", 2), free_list(&list);
	tmp = first_pointer(list, data);
	len = len_list(list);
	while (len--)
	{
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
	ft_putendl_fd("", 1);
	return (0);
}
