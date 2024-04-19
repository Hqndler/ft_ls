/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 16:26:09 by echapus           #+#    #+#             */
/*   Updated: 2024/04/19 16:54:35 by echapus          ###   ########.fr       */
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

size_t	real_len(t_list *list, size_t len, t_data data)
{
	size_t	new;
	t_list	*tmp;

	if (data.a)
		return (len);
	tmp = list;
	new = len;
	while (len--)
	{
		if (tmp->path[0] == '.' && !data.a)
			--new;
		tmp = tmp->next;
	}
	return (new);
}

char	**list_to_tab(t_list *list, t_data data, size_t len)
{
	char	**tab;
	t_list	*tmp;
	int		i;

	len = real_len(list, len, data);
	tab = malloc(sizeof(char *) * (len + 1));
	if (!tab)
		return (NULL);
	tmp = first_pointer(list, data);
	i = 0;
	while (i <= (int)len)
		tab[i++] = NULL;
	i = 0;
	while (len--)
	{
		while (tmp->path[0] == '.' && !data.a)
			tmp = following_pointer(tmp, data);
		tab[i++] = tmp->path;
		tmp = following_pointer(tmp, data);
	}
	return (tab);
}
