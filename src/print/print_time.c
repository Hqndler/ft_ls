/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:07:20 by echapus           #+#    #+#             */
/*   Updated: 2024/01/08 17:07:21 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
	15778800 ~= 30*6*24*60*60
			  -> is number of seconds for 30.4375*6 days (approx 6mounths)
*/
void	print_time(time_t lastmodified, t_data data)
{
	char		buffer[13];
	char		*str;

	memset(buffer, 0, 13);
	str = ctime(&lastmodified);
	ft_strlcpy(buffer, &str[4], 8);
	if (data.currenttime - lastmodified > 15778800)
	{
		buffer[7] = ' ';
		ft_strlcat(&buffer[8], &str[20], 5);
	}
	else
		ft_strlcat(&buffer[7], &str[11], 6);
	buffer[12] = ' ';
	write(1, buffer, 13);
}
