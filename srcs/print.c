/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:39:35 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/23 06:39:51 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dirname(t_opts *opts, char *directory) {
	if (directory) {
		if (opts->ur)
			printf("%s:\n", directory);
	}
}

bool	print_total(t_list *ptr, t_opts *opts) {
	int		len;
	t_stat	stat;

	if (!opts->l)
		return (true);
	len = 0;
	while (ptr) {
		if (lstat(ptr->content, &stat) < 0)
			break ;
		len += stat.st_blocks / 2;
		ptr = ptr->next;
	}
	printf("total %d\n", len);
	return (0);
}
