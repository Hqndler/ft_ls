#include "ft_ls.h"

static int	fill_mounth(char *buff, const char *name)
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
	buff[(*index)++] = ' ';
	buff[(*index)++] = m + 48;
	buff[(*index)++] = c + 48;
	buff[(*index)++] = d + 48;
	buff[(*index)++] = u + 48;
}

void	print_time(time_t lastmodified)
{
	char		buffer[13];
	time_t		currenttime;
	struct tm	*now;
	struct tm	*timeinfo;
	int			i;

	currenttime = time(NULL);
	now = localtime(&currenttime);
	timeinfo = localtime(&lastmodified);
	i = get_mounth(buffer, timeinfo->tm_mon);
	if (timeinfo->tm_mday < 10)
		buffer[i++] = ' ';
	fill_number(buffer, timeinfo->tm_mday, &i, ' ');
	if (timeinfo->tm_year != now->tm_year)
		fill_year(buffer, timeinfo->tm_year, &i);
	else
	{
		if (timeinfo->tm_hour < 10)
			buffer[i++] = '0';
		fill_number(buffer, timeinfo->tm_hour, &i, ':');
		if (timeinfo->tm_min < 10)
			buffer[i++] = '0';
		fill_number(buffer, timeinfo->tm_min, &i, 0);
	}
	write(1, buffer, 12);
}
