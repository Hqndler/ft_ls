/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:31:28 by echapus           #+#    #+#             */
/*   Updated: 2024/04/19 16:26:59 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_data(t_data *data)
{
	struct winsize	ws;

	data->a = false;
	data->l = false;
	data->recursive = false;
	data->r = false;
	data->t = false;
	data->currenttime = time(NULL);
	data->total_block_count = 0;
	data->bytespace = 0;
	data->linkspace = 0;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1)
		data->ws_col = 80;
	else
		data->ws_col = ws.ws_col;
}

static int	re_main(t_data data, int res, char **args)
{
	int	arg;

	arg = -1;
	while (args[++arg])
	{
		if (args[arg][0] == '-')
			continue ;
		ft_strlcpy(data.cwd, args[arg], PATH_MAX);
		ft_strlcpy(data.dir, args[arg], PATH_MAX);
		if (ft_ls_recursive(data, data.cwd))
			return (1);
		--res;
	}
	if (res == 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		res;

	res = 0;
	init_data(&data);
	if (argc >= 2)
		res = parse_args(&argv[1], &data, 0);
	if (res)
		return (re_main(data, res, &argv[1]));
	if (!getcwd(data.cwd, PATH_MAX))
		return (perror("pwd"), 1);
	ft_strlcpy(data.dir, data.cwd, PATH_MAX);
	return (ft_ls_recursive(data, data.cwd));
}
