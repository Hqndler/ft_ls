#include "ft_ls.h"

void	print_filename(char *name, bool l, bool a)
{
	if (name[0] == '.' && !a)
		return ;
	if (l)
		return ft_putendl_fd(name, 1);
	ft_putstr_fd(name, 1);
	ft_putstr_fd("  ", 1);
}