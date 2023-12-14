#include "ft_ls.h"

static int	list_new_elem_str(t_list **new, char *elem)
{
	(*new) = malloc(sizeof(t_list));
	if (*new == NULL)
		return (0);
	(*new)->path = ft_strdup(elem);
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

int	list_addtop(t_list **list, char *elem)
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
		(*list) = new;
	}
	return (1);
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

int	get_index(t_list *list, char *str)
{
	t_list	*tmp;
	size_t	len;

	tmp = list->prev;
	len = len_list(list) + 1;
	while (--len)
	{
		if (ft_strcmp(tmp->path, str))
			return (len);
		tmp = tmp->prev;
	}
	return (0);
}

int	insert_list(t_list **list, char *str, int index)
{
	t_list	*new;
	t_list	*tmp;
	int		i;

	if (!list_new_elem_str(&new, str))
		return (0);
	if (!(*list))
		add_first(list, new);
	else
	{
		i = -1;
		tmp = *list;
		if (index > (int)len_list(*list))
			index = (int)len_list(*list);
		while (++i < index)
			tmp = tmp->next;
		new->prev = tmp->prev;
		new->next = tmp;
		tmp->prev->next = new;
		tmp->prev = new;
	}
	return (1);
}

void	print_list(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	printf("[");
	while (list && tmp->next != list)
	{
		printf("\"%s\", ", tmp->path);
		tmp = tmp->next;
	}
	if (list)
		printf("\"%s\"", tmp->path);
	printf("]\n");
}

void	free_list(t_list **list)
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
}

static void	sort_tab_name(t_list ***tab, size_t len){
	size_t	i;
	size_t	j;
	t_list	*tmp;

	i = -1;
	while(++i < len - 1){
		j = -1;
		while (++j < len - 1){
			if (ft_strcmp((*tab)[j]->path, (*tab)[j + 1]->path) > 0){
				tmp = (*tab)[j];
				(*tab)[j] = (*tab)[j + 1];
				(*tab)[j + 1] = tmp;
			}
		}
	}
}

static void	relink_tab(t_list ***tab, size_t len){
	size_t	index;

	index = -1;
	while (++index < len){
		(*tab)[index]->prev = (*tab)[(index - 1 + len) % len];
		(*tab)[index]->next = (*tab)[(index + 1) % len];
	}
}

int	sort_list_name(t_list **list)
{
	t_list	*tmp;
	t_list	**tab;
	size_t	index;
	size_t	len;
	
	len = len_list(*list);
	if (!len || len == 1)
		return 1;
	tab = malloc(sizeof(t_list) * len);
	if (!list)
		return (0);
	tab[len - 1] = NULL;
	tmp = *list;
	index = 0;
	while (tmp->next != *list)
	{
		tab[index++] = tmp;
		tmp = tmp->next;
	}
	tab[index++] = tmp;
	sort_tab_name(&tab, len);
	relink_tab(&tab, len);
	*list = tab[0];
	return free(tab), 1;
}
