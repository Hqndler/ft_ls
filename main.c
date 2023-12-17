#include "ft_ls.h"

void	init_data(t_data *data){
	data->a = false;
	data->l = false;
	data->R = false;
	data->r = false;
	data->t = false;
	data->currenttime = time(NULL);
	data->total_block_count = 0;
	data->bytespace = 0;
	data->linkspace = 0;
}

void	parse_args(char **args, t_data *data){
	int		arg;
	int		i;
	char	*tmp;

	arg = -1;
	i = -1;
	while (args[++arg]){
		tmp = args[arg];
		while (tmp[++i]){
			if (tmp[i] == 'a')
				data->a = true;
			if (tmp[i] == 'l')
				data->l = true;
			if (tmp[i] == 'R')
				data->R = true;
			if (tmp[i] == 'r')
				data->r = true;
			if (tmp[i] == 't')
				data->t = true;
		}
	}
}

static int	size_len(long long bytes){
	int	size;

	size = 1;
	while (bytes >= 10){
		++size;
		bytes /= 10;
	}
	return size;
}

int	open_stat(t_list *list){
	t_list	*actual;

	actual = list->prev;
	if (!stat(actual->path, &(actual->file_stat)))
		return 1;
	else
		perror("Error while getting file stat");
	return 0;
}

void	get_bytes(t_list *list, t_data *data){
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

int main(int argc, char** argv){
	t_data	data;
	t_list	*list;

	list = NULL;

	init_data(&data);

	if (argc >= 2)
		parse_args(&argv[1], &data);
	DIR *dir = NULL;
	char	cwd[PATH_MAX]; //4096

	if (!getcwd(cwd, PATH_MAX)){
		perror("pwd");
		exit(1);
	}

	dir = opendir(cwd);
	if (!dir){
		perror("opendir");
		exit(1);
	}

	struct dirent	*fileread = NULL;

	while (1){
		fileread = readdir(dir);
		if (!fileread)
			break;
		if (!list_append(&list, fileread->d_name) || !open_stat(list))
			return closedir(dir), free_list(&list);
		get_bytes(list, &data);
	}
	closedir(dir);
	printf("total %ld\n", data.total_block_count / 2); // division by 2 bc ls count by blocks of 1024b and this count for 512b blocks
	if (!sort_list_name(&list, ALPHA))
		return free_list(&list);
	t_list *tmp = list;
	while (tmp->next != list){
		print_permission_link(tmp, data);
		print_owner_group(list);
		print_size(tmp, data);
		print_time(tmp->file_stat.st_mtime, data);
		ft_putendl_fd(tmp->path, 1);
		tmp = tmp->next;
	}
	print_permission_link(tmp, data);
	print_owner_group(list);
	print_size(tmp, data);
	print_time(tmp->file_stat.st_mtime, data);
	ft_putendl_fd(tmp->path, 1);
	free_list(&list);
	return 0;
}
