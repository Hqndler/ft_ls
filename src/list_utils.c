/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:25:12 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:29:58 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	list_new_elem_str(t_list **new, char *elem)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->path = ft_strdup(elem);
	if (!(*new)->path)
		return (free(*new), (0));
	(*new)->spacesize = 0;
	(*new)->spacelink = 0;
	(*new)->bytes = 0;
	(*new)->dir = false;
	(*new)->next = NULL;
	(*new)->prev = NULL;
	return (1);
}

static void	add_first(t_list **list, t_list *new)
{
	(*list) = new;
	(*list)->prev = *list;
	(*list)->next = *list;
}

int	list_append(t_list **list, char *elem)
{
	t_list	*new;

	if (!list_new_elem_str(&new, elem))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		new->prev = (*list)->prev;
		new->next = (*list);
		(*list)->prev->next = new;
		(*list)->prev = new;
	}
	return (1);
}

size_t	len_list(t_list *list)
{
	t_list	*tmp;
	size_t	i;

	if ((list))
	{
		tmp = list;
		i = 1;
		while (tmp->next != list)
		{
			++i;
			tmp = tmp->next;
		}
		return (i);
	}
	return (0);
}

int	free_list(t_list **list)
{
	t_list	*tmp;
	t_list	*current;

	current = *list;
	while (current->next != *list)
	{
		tmp = current;
		current = current->next;
		free(tmp->path);
		free(tmp);
	}
	free(current->path);
	free(current);
	*list = NULL;
	return (1);
}
