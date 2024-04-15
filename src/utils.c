/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:26:09 by echapus           #+#    #+#             */
/*   Updated: 2024/04/15 18:46:02 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_list	*first_pointer(t_list *list, t_data data)
{
	if (data.r)
		return (list->prev);
	return (list);
}
	// return ((data.r) ? list->prev : list);

t_list	*following_pointer(t_list *list, t_data data)
{
	if (data.r)
		return (list->prev);
	return (list->next);
}
	// return ((data.r) ? list->prev : list->next);

char	**list_to_tab(t_list *list, t_data data, size_t len)
{
	char	**tab;
	t_list	*tmp;
	int		i;

	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return NULL;
	tmp = first_pointer(list, data);
	tab[len] = NULL;
	i =  0;
	while (i < (int)len)
	{
		tab[i++] = tmp->path;
		tmp = following_pointer(tmp, data);
	}
	tab[0] = tmp->path;
	return tab;
}

int	tab_strlen(char **tab, size_t len, t_data data)
{
	int		total;
	int		i;

	total = 0;
	i = -1;
	while (++i < (int)len)
	{
		if (tab[i][0] == '.' && !data.a)
			continue;
		total += (int)ft_strlen(tab[i]) + 2;
	}
	return total;
}
