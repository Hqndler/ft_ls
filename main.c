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

int main(int argc, char** argv){
	t_data	data;
	t_list	*list;

	list = NULL;

	init_data(&data);

	if (argc >= 2)
		parse_args(&argv[1], &data);
	char	cwd[PATH_MAX]; //4096

	if (!getcwd(cwd, PATH_MAX))
		return perror("pwd"), 1;

	return ft_ls(data, list, cwd);
}
