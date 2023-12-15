#include "ft_ls.h"

void	print_size(t_list *actual, t_data data){
	int	nb_space;

	nb_space = data.bytespace - actual->spacesize;
	// printf("\nprintf size [%d] [%d] [%d]\n", nb_space, actual->spacesize, data.bytespace);
	while (nb_space-- > 0)
		write(1, " ", 1);
	ft_putnbr_fd(actual->bytes, 1);
}