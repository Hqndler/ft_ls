/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echapus <echapus@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:01:24 by echapus           #+#    #+#             */
/*   Updated: 2024/04/19 16:27:34 by echapus          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <unistd.h> //write
# include <sys/types.h> //opendir, closedir
# include <sys/stat.h> //stat, lstat
# include <dirent.h> //readdir
# include <pwd.h> // pwd
# include <grp.h> //getgrgid getpwuid
# include <sys/xattr.h> //listxattr, getxattr
# include <time.h> //time, ctime
# include <fcntl.h> //readlink
# include <stdlib.h> //malloc, free, exit
# include <errno.h> //perror
# include <string.h> //strerror
# include <limits.h> // PATH_MAX
# include <stdio.h> // printf
# include <stdbool.h> // bool
# include <sys/ioctl.h> //ioctl winsize
# include "../Libft/src/libft.h" //
# include <linux/limits.h>

typedef struct s_data{
	bool		a;
	bool		l;
	bool		recursive;
	bool		r;
	bool		t;
	bool		arg_dir;
	__blkcnt_t	total_block_count;
	time_t		currenttime;
	int			bytespace;
	int			linkspace;
	char		cwd[PATH_MAX];
	char		dir[PATH_MAX];
	int			ws_col;
}				t_data;

typedef struct s_list
{
	char			*path;
	int				spacesize;
	int				spacelink;
	off_t			bytes;
	bool			dir;
	struct stat		file_stat;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

# define ALPHA 0
# define TIME 1

// List func
int		list_append(t_list **list, char *elem);
size_t	len_list(t_list *list);
int		free_list(t_list **list);
int		compare_function(t_list *first, t_list *second, int mode);
void	quick_sort_tab(t_list ***tab, int low, int high, int mode);
int		sort_list_name(t_list **list, int mode);

int		size_len(long long bytes);
t_list	*first_pointer(t_list *list, t_data data);
t_list	*following_pointer(t_list *list, t_data data);
char	**list_to_tab(t_list *list, t_data data, size_t len);
int		tab_strlen(char **tab, size_t len, t_data data);

int		parse_args(char **args, t_data *data, int arg);
void	print_time(time_t lastmodified, t_data data);
void	print_size(t_list *actual, t_data data);
void	print_owner_group(t_list *list);
void	print_permission_link(t_list *list, t_data data);
int		get_dir_files(char *cwd, t_data *data, t_list **list);
int		ft_ls_recursive(t_data data, char *cwd);
int		ft_ls(t_data data, t_list *list, size_t len);
void	print_total(blkcnt_t total, bool l);
void	print_filename_only(t_list *list, t_data data, size_t len);
void	print_filename(char *name, t_data data);
void	print_location(t_data data, char *cwd);

#endif