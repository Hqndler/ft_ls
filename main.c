#include "ft_ls.h"

void	init_data(t_data *data){
	data->a = false;
	data->l = false;
	data->R = false;
	data->r = false;
	data->t = false;
	data->path = NULL;
	data->total_block_size = 0;
	data->bytespace = 0;
}

void	parse_args(char **args, t_data *data){
	int		arg;
	int		i;
	char	*tmp;

	arg = -1;
	i = -1;
	while (args[++arg]){
		if (args[arg][0] != '-')
			data->path = ft_strdup(args[arg++]);
		else{
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

void	file_bytes(t_list *list, t_data *data){
	t_list		*actual = list->prev;
	__blksize_t	block_size;
	struct stat	file_stat;
	int			tmp;

	if (!stat(actual->path, &file_stat)){
		actual->bytes = file_stat.st_size;
		block_size = file_stat.st_blksize;
		actual->block_size = (actual->bytes + block_size - 1) / block_size;
		data->total_block_size += actual->block_size;
		tmp = size_len(file_stat.st_size);
		actual->spacesize = tmp;
		if (tmp > data->bytespace)
			data->bytespace = tmp;
	}
	else
		perror("Error while getting file size / bytes");
}

void	file_time(t_list *list){
	struct stat	file_stat;
	t_list		*actual;

	actual = list->prev;

	if (!stat(actual->path, &file_stat)){
		actual->lastmodified = file_stat.st_mtime;
		// actual->timeinfo = localtime(&last_modified);
	}
	else
		perror("Error while getting file time");
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
		file_bytes(list, &data);
		file_time(list);
		// printf("%ld %s\n", list->prev->bytes, list->prev->path);
	}
	sort_list_name(&list);
	t_list *tmp = list;
	while (tmp->next != list){
		// printf("%ld %s\n", tmp->bytes, tmp->path);
		// ft_putnbr_fd(tmp->bytes, 1);
		print_size(tmp, data);
		write(1, " ", 1);
		print_time(tmp->lastmodified);
		printf(" %s\n", tmp->path);
		tmp = tmp->next;
	}
	print_size(tmp, data);
	write(1, " ", 1);
	print_time(tmp->lastmodified);
	printf(" %s\n", tmp->path);
	free_list(&list);
	closedir(dir);
	return 0;
}
