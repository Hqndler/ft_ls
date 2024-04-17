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

int	space_tab(char **tab, int start, int lines, int length)
{
	int	len;
	int	longest;
	int	startlen;
	int	i;
	int	count;

	startlen = ft_strlen(tab[start]);
	longest = startlen;
	i = (start % lines) * -1;
	count = 0;
	while (++count <= lines)
	{
		if ((start + i) < length)
		{
			len = ft_strlen(tab[start + i++]);
			if (len > longest)
				longest = len;
		}
	}
	if (longest > startlen)
		return (longest - startlen);
	return (0);
}

bool	try_write_tab(char **tab, int lines, int len, t_data data)
{
	int	ret;
	int	line;
	int	i;

	line = -1;
	ret = 0;
	while (++line < lines)
	{
		i = line;
		while (i < len)
		{
			ret += (int)ft_strlen(tab[i]) + space_tab(tab, i, lines, len) + 2;
			i += lines;
		}
		if (ret > data.ws_col)
			return (false);
		ret = 0;
	}
	return (true);
}

void	print_tab(char **tab, int lines, int len)
{
	int	line;
	int	i;
	int	space;

	line = -1;
	space = 0;
	while (++line < lines)
	{
		i = line;
		while (i < len)
		{
			ft_putstr_fd(tab[i], 1);
			space = space_tab(tab, i, lines, len) + 2;
			while (space-- != 0)
				ft_putchar_fd(' ', 1);
			i += lines;
		}
		ft_putendl_fd("", 1);
	}
}

void	print_filename_only(t_list *list, t_data data, size_t len)
{
	char	**tab;
	int		lines;

	tab = list_to_tab(list, data, len);
	if (!tab)
		return ;
	lines = 1;
	len = 0;
	while (tab[len])
		++len;
	while (true)
	{
		if (try_write_tab(tab, lines, (int)len, data) == true)
			break ;
		else
			++lines;
	}
	print_tab(tab, lines, (int)len);
	free(tab);
}

void	print_filename(char *name, t_data data)
{
	char	buffer[4096];
	char	tmp[4096];
	int		ret;

	if (name[0] == '.' && !data.a)
		return ;
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
