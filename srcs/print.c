/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:39:35 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 09:02:51 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dirname(t_opts *opts, char *directory) {
	static int nl = 0;
	
	if (directory) {
		if (nl > 0 && opts->ur) {
			ft_putchar_fd('\n', 1);
			ft_putstr_fd(directory, 1);
			ft_putchar_fd('\n', 1);
		}
		else if (nl > 0) {
			ft_putstr_fd(directory, 1);
			ft_putchar_fd('\n', 1);
		}
	}
	nl++;
}

bool	print_total(t_list *ptr, t_opts *opts) {
	int		len;
	t_stat	stat;

	if (!opts->l)
		return (true);
	len = 0;
	while (ptr) {
		if (lstat(ptr->content, &stat) < 0) {
			printf("ft_ls: %s: %s\n", (char *)ptr->content, strerror(errno));
			break ;
		}
		len += stat.st_blocks / 2;
		ptr = ptr->next;
	}
	ft_putstr_fd("total ", 1);
	ft_putnbr_fd(len, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}
