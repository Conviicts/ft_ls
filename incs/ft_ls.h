#ifndef FT_LS_H
#define FT_LS_H

#include <stdbool.h>
#include <stdarg.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "libft.h"

typedef struct stat		t_stat;
typedef struct passwd	t_passwd;
typedef struct group	t_group;

typedef struct s_opts {
	bool	l;
	bool	ur;
	bool	a;
	bool	r;
	bool	t;
}				t_opts;

typedef struct s_display {
	int		st_nlink;
	int		st_size;
	int		user_len;
	int		grp_len;
}	t_display;


typedef struct	s_ls {
	t_opts		opts;
}				t_ls;

bool	print_total(t_list *ptr, t_opts *opts);
void	print_dirname(t_opts *opts, char *directory);

bool	open_dir(t_opts *opts, char *directory);

t_list	*sortlist(t_list **ptr, t_opts *opts);

bool	display(t_opts *opts, t_list *ptr, t_display *dsp);

bool	ft_ls2(t_opts *opts, t_list *ptr);

int		get_grp_max(t_list *ptr);
int		get_user_max(t_list *ptr);
int		get_st_nlink_max(t_list *ptr);
int		get_st_size_max(t_list *ptr);

char	*gettime(time_t sec);
void	print_rights(int mode);
void	print_stsize(int len, int st_size);
void	print_stnlink(int len, int st_nlink);
void	print_usr_grp(t_display *dsp, char *passwd, char *group);

void	printList(t_list *node);
void	bubbleSort(t_list *start);

bool	error(char *str);

#endif