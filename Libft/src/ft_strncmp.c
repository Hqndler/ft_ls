/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:26:41 by echapus           #+#    #+#             */
/*   Updated: 2022/08/18 09:58:20 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return (-1);
	i = 0;
	while ((s1[i] && s2[i]) && i < n - 1)
	{
		if (s1[i] == s2[i])
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;

	if (!s1 || !s2)
		return (0);
	i = 0;
	while (s1[i] && s2[i])
	{
		if ((s1[i] == s2[i]))
			i++;
		else
			break ;
	}
	return (s1[i] - s2[i]);
}

int	ft_strcasecmp(const char *s1, const char *s2)
{
	int		i;
	char	c1;
	char	c2;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i]){
		c1 = ft_tolower(s1[i]);
		c2 = ft_tolower(s2[i]);
		if (c1 < c2)
			return (-1);
		if (c1 > c2)
			return (1);
		++i;
	}
	return (0);
}