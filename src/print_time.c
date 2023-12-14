#include "ft_ls.h"

static void	fill_mounth(char *buff, const char *name){
	buff[0] = name[0];
	buff[1] = name[1];
	buff[2] = name[2];
}

static void	get_mounth(char *buff, int nb){
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

void	print_time(time_t lastmodified){
	char		mounth[4];
	time_t		currenttime;
	struct tm	*now;
	struct tm	*timeinfo;

	currenttime = time(NULL);
	now = localtime(&currenttime);
	timeinfo = localtime(&lastmodified);

	get_mounth(mounth, timeinfo->tm_mon);
	// mounth[3] = 0;
	// printf("[%s]\n", mounth);
	printf("\a");
	write(1, mounth, 3);
	write(1, " ", 1);
	if (timeinfo->tm_mday < 10)
		write(1, " ", 1);
	ft_putnbr_fd(timeinfo->tm_mday, 1);
	write(1, " ", 1);
	if (timeinfo->tm_year != now->tm_year){
		write(1, " ", 1);
		ft_putnbr_fd(timeinfo->tm_year, 1);
	}
	else{
		ft_putnbr_fd(timeinfo->tm_hour, 1);
		write(1, ":", 1);
		if (timeinfo->tm_min < 10)
			write(1, "0", 1);
		ft_putnbr_fd(timeinfo->tm_min, 1);
	}
}