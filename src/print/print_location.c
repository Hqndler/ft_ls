#include "ft_ls.h"

void	print_location(t_data data, char *cwd)
{
	int	i;

	if (!data.R)
		return ;
	i = 0;
	while (cwd[i] && data.cwd[i] && cwd[i] == data.cwd[i])
		++i;
	write(1, ".", 1);
	ft_putstr_fd(&(cwd[i]), 1);
	write(1, ":\n", 2);
}