/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_filename.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:11:52 by echapus           #+#    #+#             */
/*   Updated: 2024/04/15 18:47:00 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	simple_print(char **tab, size_t len, t_data data)
{
	while (--len)
	{
		if (!data.a && tab[len][0] == '.')
			continue;
		ft_putstr_fd(tab[len], 1);
		ft_putstr_fd("  ", 1);
	}
	if (!data.a && tab[len][0] == '.')
		return (free(tab));
	ft_putstr_fd(tab[len], 1);
	ft_putstr_fd("  ", 1);
	ft_putendl_fd("", 1);
	free(tab);
}

void 	longest_in_col(char **tab, t_data data, int lines)
{
	int	i;
	int	i_longest;
	int	longest;
	int	len;

	i = -1;
	len = 0;
	longest = 0;
	while (++i <= lines)
	{
		if (tab[i][0] == '.' && !data.a)
			continue ;
		len = ft_strlen(tab[i]);
		if (len > longest)
		{
			longest = len;
			i_longest = i;
		}
	}
	printf("%s est le plus long avec %d\n", tab[i_longest], longest);
}

void	print_filename_only(t_list *list, t_data data, size_t len)
{
	char	**tab;
	int		total_len;
	int		lines;

	tab = list_to_tab(list, data, len);
	if (!tab)
		return ;
	total_len = tab_strlen(tab, len, data);
	printf("total len %d et ws_col %d\n", total_len, data.ws_col);
	if (total_len < data.ws_col)
		return (simple_print(tab, len, data));
	lines = (total_len / data.ws_col);
	if (total_len % data.ws_col)
		++lines;
	printf("nombre de lines %d par colones, total %d et ws_col %d\n", lines, total_len, data.ws_col);
	longest_in_col(tab, data, lines);
	// simple_print(tab, len, data);
}

void	print_filename(char *name, t_data data)
{
	char	buffer[4096];
	char	tmp[4096];
	int		ret;

	if (name[0] == '.' && !data.a)
		return ;
	// if (!l)
		// return (ft_putstr_fd(name, 1), ft_putstr_fd("  ", 1));
	ft_putstr_fd(name, 1);
	ft_bzero(tmp, 4096);
	ft_strlcat(tmp, data.cwd, 4096);
	ft_strlcat(tmp, "/", 4096);
	ft_strlcat(tmp, name, 4096);
	ret = readlink(tmp, buffer, 4095);
	if (ret != -1)
	{
		buffer[ret] = 0;
		ft_putstr_fd(" -> ", 1);
		ft_putendl_fd(buffer, 1);
	}
	else
		ft_putendl_fd("", 1);
}
