#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	ft_printf_putchar_fd(char c, int fd);
int	ft_printf_putstr_fd(char *str, int fd);
int ft_pointer_fd(long long unsigned int ptr, int fd);
int	ft_nbr_fd(int nbr, int fd);
int	ft_unbr_fd(unsigned int nbr, int fd);
int	ft_putnbr_base_fd(unsigned int nbr, int fd, char c);
int	ft_write_type(char c, va_list arg);

#endif