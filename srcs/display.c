/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:57:17 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 05:29:54 by jode-vri         ###   ########.fr       */
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

void print_rights(int mode) {
	char c;

	c = '-';
	c = (S_ISDIR(mode)) ? 'd' : c;
	c = (S_ISSOCK(mode)) ? 's' : c;
	c = (S_ISBLK(mode)) ? 'b' : c;
	c = (S_ISLNK(mode)) ? 'l' : c;
	c = (S_ISFIFO(mode)) ? 'p' : c;
	c = (S_ISCHR(mode)) ? 'c' : c;
	printf("%c", c);
	printf("%c", (mode & S_IRUSR) ? 'r' : '-');
	printf("%c", (mode & S_IWUSR) ? 'w' : '-');
	printf("%c", (mode & S_IXUSR) ? 'x' : '-');
	printf("%c", (mode & S_IRGRP) ? 'r' : '-');
	printf("%c", (mode & S_IWGRP) ? 'w' : '-');
	printf("%c", (mode & S_IXGRP) ? 'x' : '-');
	printf("%c", (mode & S_IROTH) ? 'r' : '-');
	printf("%c", (mode & S_IWOTH) ? 'w' : '-');
	printf("%c", (mode & S_IXOTH) ? 'x' : '-');
} 

void	print_l(char *content) {
	(void)content;
	t_stat		st;
	t_passwd	*passwd;
	t_group		*group;
	char		*date;

	if (lstat(content, &st) == -1)
		return ;
	passwd = getpwuid(st.st_uid);
	group = getgrgid(st.st_gid);
	date = gettime(st.st_mtime);
	print_rights(st.st_mode);
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode)) {
		printf("aaa %3lu %s %8s %s ", st.st_nlink, passwd->pw_name, group->gr_name, date);
	} else {
		printf(" %3lu %s %s %7ld %s ", st.st_nlink, passwd->pw_name, group->gr_name, st.st_size, date);
	}
}

void	print_name(t_opts *opts, char *name) {
	t_stat	st;
	char	*res;
	char	tmp[4096];
	int		len;
	
	res = ft_strrchr(name + 1, '/');
	res = !res ? name : res + 1;
	if (lstat(name, &st) == -1)
		return ;
	printf("%s", (char *)res);
	if (opts->l && S_ISLNK(st.st_mode)) {
		if ((len = readlink(name, tmp, 4096)) == -1) {
			printf("ft_ls: %s: %s\n", name, strerror(errno));
			return ;
		}
		tmp[len] = '\0';
		printf(" -> %s", tmp);
	}
	// printf("\n");
}

void	print_column(char *content) {
	t_stat	st;
	char	*res;

	res = ft_strrchr(content + 1, '/');
	res = !res ? content : res + 1;
	if (lstat(content, &st) == -1)
		return ;
	printf("%s  ", (char *)res);
}

bool	display(t_opts *opts, t_list *ptr) {
	(void)opts;

	while (ptr) {
		if (opts->l) {
			print_l((char *)ptr->content);
			print_name(opts, (char *)ptr->content);
		} else {
			print_column((char *)ptr->content);
		}
		ptr = ptr->next;
		if (ptr && opts->l)
			printf("\n");
	}
	// if (!opts->l)
		printf("\n");
	return (true);
}