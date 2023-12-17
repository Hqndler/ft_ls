#ifndef FT_LS_H
#define FT_LS_H

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
# include "../Libft/src/libft.h" //

typedef struct s_data{
	bool		a; //all
	bool		l; //long listing
	bool		R; //recursive
	bool		r; //reverse
	bool		t; //sort by time
	// char		*path;
	off_t		total_bytes;
	time_t		currenttime;
	// __blksize_t	total_block_size;
	int			bytespace;
	int			linkspace;
} t_data;

typedef struct s_list
{
	char			*path;
	int				spacesize;
	int				spacelink;
	off_t			bytes;
	__blksize_t		block_size;
	// time_t			lastmodified;
	struct stat		file_stat;
	struct s_list	*prev;
	struct s_list	*next;
}					t_list;

# define ALPHA 0
# define TIME 1

// List func
int		list_addtop(t_list **list, char *elem);
int		list_append(t_list **list, char *elem);
size_t	len_list(t_list *list);
int		get_index(t_list *list, char *str);
int		insert_list(t_list **list, char *str, int index);
void	print_list(t_list *list);
void	free_list(t_list **list);
int		sort_list_name(t_list **list, int mode);

void	print_time(time_t lastmodified, t_data);
void	print_size(t_list *actual, t_data data);
void    print_owner_group(t_list *list);
void	print_right_link(t_list *list, t_data data);

#endif