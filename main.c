#include "ft_ls.h"

void	init_data(t_data *data){
	data->a = false;
	data->l = false;
	data->R = false;
	data->r = false;
	data->t = false;
	// data->path = NULL;
	data->currenttime = time(NULL);
	// data->total_block_size = 0;
	data->total_bytes = 0;
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
	// printf("%s\t\t%p\n", actual->path, &(actual->file_stat));
	if (!stat(actual->path, &(actual->file_stat))){
		// printf("%o\n", actual->file_stat.st_mode & 0777);
		return 0;
	}
	else
		perror("Error while getting file stat");
	return 1;
}

void	get_bytes(t_list *list, t_data *data){
	t_list	*actual;
	int		slen;

	actual = list->prev;
	data->total_bytes += actual->file_stat.st_size;
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
		list_append(&list, fileread->d_name);
		open_stat(list);
		get_bytes(list, &data);
	}
	printf("total %ld\n", data.total_bytes / 1024); // comprends pas pourquoi ça donne pas un bon total
	sort_list_name(&list, ALPHA);
	t_list *tmp = list;
	while (tmp->next != list){
		print_permission_link(tmp, data);
		print_owner_group(list);
		print_size(tmp, data);
		print_time(tmp->file_stat.st_mtime, data);
		printf("%s\n", tmp->path);
		tmp = tmp->next;
	}
	print_permission_link(tmp, data);
	print_owner_group(list);
	print_size(tmp, data);
	print_time(tmp->file_stat.st_mtime, data);
	printf("%s\n", tmp->path);
	free_list(&list);
	closedir(dir);
	return 0;
}
