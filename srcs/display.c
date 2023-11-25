/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:57:17 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/25 03:34:04 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

	if (lstat(content, &st) == -1){
		error(content);
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
	if (lstat(name, &st) == -1){
		error(name);
		return ;
	}
	ft_putstr_fd((char *)res, 1);
	if (opts->l && S_ISLNK(st.st_mode)) {
		if ((len = readlink(name, tmp, 4096)) == -1){
			error(name);
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
		error(content);
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