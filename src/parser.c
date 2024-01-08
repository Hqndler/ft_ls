/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:24:08 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:34:17 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	parse_option(char *arg, t_data *data)
{
	int	i;

	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'a')
			data->a = true;
		else if (arg[i] == 'l')
			data->l = true;
		else if (arg[i] == 'R')
			data->recursive = true;
		else if (arg[i] == 'r')
			data->r = true;
		else if (arg[i] == 't')
			data->t = true;
		else
		{
			ft_putstr_fd("ft_ls : invalid option '", 2);
			ft_putchar_fd(arg[i], 2);
			ft_putendl_fd("'", 2);
			exit(2);
		}
	}
}

int	parse_args(char **args, t_data *data, int arg)
{
	char	*tmp;

	tmp = args[arg];
	if (!tmp)
		return (0);
	if (!ft_strcmp(tmp, "--recursive"))
		return (data->recursive = true, parse_args(args, data, arg + 1));
	else if (!ft_strcmp(tmp, "--reverse"))
		return (data->r = true, parse_args(args, data, arg + 1));
	else if (!ft_strcmp(tmp, "--all"))
		return (data->a = true, parse_args(args, data, arg + 1));
	else if (tmp[0] == '-' && tmp[1] != '-')
		return (parse_option(tmp, data), parse_args(args, data, arg + 1));
	else if (tmp[0] == '-' && tmp[1] == '-')
	{
		ft_putstr_fd("ft_ls : unrecognized option '", 2);
		ft_putstr_fd(args[arg], 2);
		ft_putendl_fd("'", 2);
		exit(2);
	}
	return (1 + parse_args(args, data, arg + 1));
}
