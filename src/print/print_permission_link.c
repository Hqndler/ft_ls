/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_permission_link.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:12:49 by echapus           #+#    #+#             */
/*   Updated: 2024/04/04 15:23:18 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	check_perm(char *buff, mode_t perm, int *index, char c)
{
	if (perm)
		buff[*index] = c;
	(*index)++;
}

static void	check_all_perm(char *buff, int *index, mode_t mode)
{
	check_perm(buff, (mode & S_IRUSR), index, 'r');
	check_perm(buff, (mode & S_IWUSR), index, 'w');
	check_perm(buff, (mode & S_IXUSR), index, 'x');
	check_perm(buff, (mode & S_IRGRP), index, 'r');
	check_perm(buff, (mode & S_IWGRP), index, 'w');
	check_perm(buff, (mode & S_IXGRP), index, 'x');
	check_perm(buff, (mode & S_IROTH), index, 'r');
	check_perm(buff, (mode & S_IWOTH), index, 'w');
	check_perm(buff, (mode & S_IXOTH), index, 'x');
}

void	print_permission_link(t_list *list, t_data data)
{
	mode_t	mode;
	t_list	*actual;
	char	buff[11];
	int		i;

	actual = list;
	mode = actual->file_stat.st_mode;
	i = 1;
	ft_memset(buff, '-', 10);
	if (S_ISREG(mode))
		buff[0] = '-';
	if (S_ISDIR(mode))
		buff[0] = 'd';
	if (S_ISLNK(mode))
		buff[0] = 'l';
	check_all_perm(buff, &i, mode);
	buff[i] = ' ';
	write(1, buff, 11);
	i = data.linkspace - size_len((long long)actual->file_stat.st_nlink);
	while (i-- > 0)
		write(1, " ", 1);
	ft_putnbr_fd((long)(actual->file_stat.st_nlink), 1);
	write(1, " ", 1);
}
