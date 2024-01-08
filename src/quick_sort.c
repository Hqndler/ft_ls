/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quick_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:29:27 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:30:11 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	swap_node(t_list **a, t_list **b)
{
	t_list	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int	quick_swap_partition(t_list ***tab, int low, int high, int mode)
{
	int		i;
	int		j;

	i = low - 1;
	j = low;
	while (j < high)
	{
		if (compare_function((*tab)[j], (*tab)[high], mode))
			swap_node(&((*tab)[++i]), &((*tab)[j]));
		++j;
	}
	swap_node(&((*tab)[i + 1]), &((*tab)[high]));
	return (i + 1);
}

void	quick_sort_tab(t_list ***tab, int low, int high, int mode)
{
	int	pivot;

	if (low < high)
	{
		pivot = quick_swap_partition(tab, low, high, mode);
		quick_sort_tab(tab, low, pivot - 1, mode);
		quick_sort_tab(tab, pivot + 1, high, mode);
	}
}
