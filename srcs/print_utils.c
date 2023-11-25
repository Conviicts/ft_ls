/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 03:34:12 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/25 03:34:17 by jode-vri         ###   ########.fr       */
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
