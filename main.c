#include "ft_ls.h"

void	init_data(t_data *data){
	data->a = false;
	data->l = false;
	data->R = false;
	data->r = false;
	data->t = false;
	data->path = NULL;
}

void	parse_args(char **args, t_data *data){
	int		arg;
	int		i;
	char	*tmp;

	arg = -1;
	i = -1;
	while (args[++arg]){
		if (args[arg][0] != '-')
			data->path = strdup(args[arg++]);
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

int main(int argc, char** argv){
	t_data	data;

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
		printf("%s\n", fileread->d_name);
	}
	closedir(dir);
	return 0;
}