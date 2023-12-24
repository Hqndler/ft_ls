#include "ft_ls.h"

static t_list	*first_pointer(t_list *list, t_data data){
	return ((data.r) ? list->prev : list);
}

static t_list	*following_pointer(t_list *list, t_data data){
	return ((data.r) ? list->prev : list->next);
}

int	ft_ls(t_data data, t_list *list, char *cwd)
{
	t_list	*tmp;
	size_t	len;

	if (get_dir_files(cwd, &data, &list))
		return (1);

	printf("total %ld\n", data.total_block_count / 2); // division by 2 bc ls count by blocks of 1024b and this count for 512b blocks
	if (!sort_list_name(&list, ALPHA))
		return ft_putstr_fd("malloc error", 2), free_list(&list);

	tmp = first_pointer(list, data);
	len = len_list(list);
	while (len--)
	{
		print_permission_link(tmp, data);
		print_owner_group(list);
		print_size(tmp, data);
		print_time(tmp->file_stat.st_mtime, data);
		ft_putendl_fd(tmp->path, 1);
		tmp = following_pointer(tmp, data);
	}
	free_list(&list);
	return (0);
}
