#include "ft_ls.h"

/*static int	fill_mounth(char *buff, const char *name)
{
	buff[0] = name[0];
	buff[1] = name[1];
	buff[2] = name[2];
	buff[3] = ' ';
	return (4);
}

static int	get_mounth(char *buff, int nb)
{
	buff[3] = 0;
	if (nb == 0)
		return fill_mounth(buff, "Jan");
	if (nb == 1)
		return fill_mounth(buff, "Feb");
	if (nb == 2)
		return fill_mounth(buff, "Mar");
	if (nb == 3)
		return fill_mounth(buff, "Apr");
	if (nb == 4)
		return fill_mounth(buff, "May");
	if (nb == 5)
		return fill_mounth(buff, "Jun");
	if (nb == 6)
		return fill_mounth(buff, "Jui");
	if (nb == 7)
		return fill_mounth(buff, "Aug");
	if (nb == 8)
		return fill_mounth(buff, "Sep");
	if (nb == 9)
		return fill_mounth(buff, "Oct");
	if (nb == 10)
		return fill_mounth(buff, "Nov");
	return fill_mounth(buff, "Dec");
}

static void	fill_number(char *buff, int nb, int (*index), char c)
{
	if (nb >= 10)
		buff[(*index)++] = (nb / 10) + 48;
	buff[(*index)++] = (nb % 10) + 48;
	buff[(*index)++] = c;
}

static void	fill_year(char *buff, int year, int (*index))
{
	int	m;
	int	c;
	int	d;
	int	u;

	m = year / 1000;
	year %= 1000;
	c = year / 100;
	year %= 100;
	d = year / 10;
	u = year % 10;
	buff[(*index)++] = m + 48;
	buff[(*index)++] = c + 48;
	buff[(*index)++] = d + 48;
	buff[(*index)++] = u + 48;
	buff[(*index)++] = ' ';
}*/
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
