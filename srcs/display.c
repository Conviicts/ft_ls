/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:57:17 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/25 02:50:21 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*gettime(time_t sec) {
	time_t		current;
	char		*result;
	char		*tmp;
	char		*tmp2;

	time(&current);
	if ((current - sec) > 14515200) {
		tmp = ctime(&sec);
		tmp2 = ft_substr(tmp, 4, 7);
		tmp = ft_substr(tmp, 19, 5);
		result = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	else
		result = ft_substr(ctime(&sec), 4, 12);
	return (result);
}

void	print_rights(int mode) {
	char c;

	c = '-';
	c = (S_ISDIR(mode)) ? 'd' : c;
	c = (S_ISSOCK(mode)) ? 's' : c;
	c = (S_ISBLK(mode)) ? 'b' : c;
	c = (S_ISLNK(mode)) ? 'l' : c;
	c = (S_ISFIFO(mode)) ? 'p' : c;
	c = (S_ISCHR(mode)) ? 'c' : c;
	ft_putchar_fd(c, 1);
	ft_putchar_fd((mode & S_IRUSR) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWUSR) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXUSR) ? 'x' : '-', 1);
	ft_putchar_fd((mode & S_IRGRP) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWGRP) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXGRP) ? 'x' : '-', 1);
	ft_putchar_fd((mode & S_IROTH) ? 'r' : '-', 1);
	ft_putchar_fd((mode & S_IWOTH) ? 'w' : '-', 1);
	ft_putchar_fd((mode & S_IXOTH) ? 'x' : '-', 1);
	ft_putchar_fd(' ', 1);
} 

void	print_stnlink(int len, int st_nlink) {
	int	i;

	len <= 9 ? i = 1 : 0;
	len >= 10 && len <= 99 ? i = 2 : 0;
	len >= 100 && len <= 999 ? i = 3 : 0;
	while (st_nlink > i) {
		ft_putchar_fd(' ', 1);
		st_nlink--;
	}
    ft_putnbr_fd(len, 1);
    ft_putchar_fd(' ', 1);
}

void	print_stsize(int len, int st_size) {
	int	i;

	len <= 9 ? i = 1 : 0;
	len >= 10 && len <= 99 ? i = 2 : 0;
	len >= 100 && len <= 999 ? i = 3 : 0;
	len >= 1000 && len <= 9999 ? i = 4 : 0;
	len >= 10000 && len <= 99999 ? i = 5 : 0;
	len >= 100000 && len <= 999999 ? i = 6 : 0;
	len >= 1000000 && len <= 9999999 ? i = 7 : 0;
	len >= 10000000 && len <= 99999999 ? i = 8 : 0;
	len >= 100000000 && len <= 999999999 ? i = 9 : 0;
	ft_putchar_fd(' ', 1);
	while (st_size > i) {
		ft_putchar_fd(' ', 1);
		st_size--;
	}
    ft_putnbr_fd(len, 1);
}

void	print_usr_grp(t_display *dsp, char *passwd, char *group) {
	int	len;

	len = ft_strlen(passwd);
	ft_putstr_fd(passwd, 1);
	while (len < dsp->user_len) {
		ft_putchar_fd(' ', 1);
		len++;
	}
	ft_putchar_fd(' ', 1);
	len = ft_strlen(group);
    ft_putstr_fd(group, 1);
	while (len < dsp->grp_len) {
		ft_putchar_fd(' ', 1);
		len++;
	}
}

void	print_data(t_stat st, bool size, t_display *dsp) {
    t_passwd	*passwd;
    t_group		*group;
    char		*date;
	
    passwd = getpwuid(st.st_uid);
    group = getgrgid(st.st_gid);
    date = gettime(st.st_mtime);

	print_stnlink(st.st_nlink, dsp->st_nlink);
	print_usr_grp(dsp, passwd->pw_name, group->gr_name);
    if (size)
		print_stsize(st.st_size, dsp->st_size);
    ft_putchar_fd(' ', 1);
    ft_putstr_fd(date, 1);
    ft_putchar_fd(' ', 1);

}

void	print_l(char *content, t_display *dsp) {
	t_stat		st;

	if (lstat(content, &st) == -1) {
		printf("ft_ls: %s: %s\n", content, strerror(errno));
		return ;
	}
	print_rights(st.st_mode);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
		print_data(st, false, dsp);
	else
		print_data(st, true, dsp);
}

void	print_name(t_opts *opts, char *name) {
	t_stat	st;
	char	*res;
	char	tmp[4096];
	int		len;
	
	res = ft_strrchr(name + 1, '/');
	res = !res ? name : res + 1;
	if (lstat(name, &st) == -1) {
		printf("ft_ls: %s: %s\n", name, strerror(errno));
		return ;
	}
	ft_putstr_fd((char *)res, 1);
	if (opts->l && S_ISLNK(st.st_mode)) {
		if ((len = readlink(name, tmp, 4096)) == -1) {
			ft_putstr_fd("ft_ls: ", 2);
			ft_putstr_fd(name, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(strerror(errno), 2);
			ft_putchar_fd('\n', 2);
			return ;
		}
		tmp[len] = '\0';
		ft_putstr_fd(" -> ", 1);
		ft_putstr_fd(tmp, 1);
	}
}

void	print_column(char *content) {
	t_stat	st;
	char	*res;

	res = ft_strrchr(content + 1, '/');
	res = !res ? content : res + 1;
	if (lstat(content, &st) == -1) {
		printf("ft_ls: %s: %s\n", content, strerror(errno));
		return ;
	}
	ft_putstr_fd((char *)res, 1);
	ft_putchar_fd(' ', 1);
}

bool	display(t_opts *opts, t_list *ptr, t_display *dsp) {
	while (ptr) {
		if (opts->l) {
			print_l((char *)ptr->content, dsp);
			print_name(opts, (char *)ptr->content);
		} else {
			print_column((char *)ptr->content);
		}
		ptr = ptr->next;
		if (ptr && opts->l)
			ft_putchar_fd('\n', 1);
	}
	ft_putchar_fd('\n', 1);
	return (true);
}