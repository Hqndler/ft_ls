#include "ft_ls.h"

void	print_size(t_list *actual, t_data data){
	int	nb_space;

	nb_space = data.bytespace - actual->spacesize;
	while (nb_space-- > 0)
		write(1, " ", 1);
	ft_putnbr_fd(actual->file_stat.st_size, 1);
	write(1, " ", 1);
}