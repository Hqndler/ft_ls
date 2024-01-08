/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:28:38 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:47:16 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char	*check_for_sort(char *str)
{
	if (str[0] == '.' && ft_strcmp(str, ".") && ft_strcmp(str, ".."))
		return (&str[1]);
	return (str);
}

int	compare_function(t_list *first, t_list *second, int mode)
{
	char	*s1;
	char	*s2;

	if (mode == ALPHA)
	{
		s1 = check_for_sort(first->path);
		s2 = check_for_sort(second->path);
		return (ft_strcasecmp(s1, s2) <= 0);
	}
	else if (mode == TIME)
	{
		if (first->file_stat.st_mtime == second->file_stat.st_mtime)
			return (first->file_stat.st_mtim.tv_nsec > \
			second->file_stat.st_mtim.tv_nsec);
		return (first->file_stat.st_mtime > second->file_stat.st_mtime);
	}
	return (0);
}

static void	relink_tab(t_list ***tab, size_t len)
{
	size_t	index;

	index = -1;
	while (++index < len)
	{
		(*tab)[index]->prev = (*tab)[(index - 1 + len) % len];
		(*tab)[index]->next = (*tab)[(index + 1) % len];
	}
}

int	sort_list_name(t_list **list, int mode)
{
	t_list	*tmp;
	t_list	**tab;
	size_t	index;
	size_t	len;

	len = len_list(*list);
	if (len <= 1)
		return (1);
	tab = malloc(sizeof(t_list) * len);
	if (!list)
		return (ft_putstr_fd("malloc error", 2), 0);
	tab[len - 1] = NULL;
	tmp = *list;
	index = 0;
	while (tmp->next != *list)
	{
		tab[index++] = tmp;
		tmp = tmp->next;
	}
	tab[index++] = tmp;
	quick_sort_tab(&tab, 0, len - 1, mode);
	relink_tab(&tab, len);
	*list = tab[0];
	return (free(tab), 1);
}
