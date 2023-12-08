#ifndef FT_LS_H
#define FT_LS_H

# include <unistd.h> //write
# include <sys/types.h> //opendir, closedir
# include <sys/stat.h> //stat, lstat
# include <dirent.h> //readdir
# include <pwd.h> // pwd
# include <grp.h> //getgrgid
# include <sys/xattr.h> //listxattr, getxattr
# include <time.h> //time, ctime
# include <fcntl.h> //readlink
# include <stdlib.h> //malloc, free, exit
# include <errno.h> //perror
# include <string.h> //strerror
# include <limits.h> // PATH_MAX
# include <stdio.h> // printf
# include <stdbool.h>

typedef struct s_data{
	bool	a; //all
	bool	l; //long listing
	bool	R; //recursive
	bool	r; //reverse
	bool	t; //sort by time
	char	*path;
} t_data;

#endif