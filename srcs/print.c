/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:39:35 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 06:24:02 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_dirname(t_opts *opts, char *directory) {
	static int nl = 0;
	
	if (directory) {
		if (nl > 0 && opts->ur)
			printf("\n%s:\n", directory);
		else if (nl > 0)
			printf("%s:\n", directory);
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
		if (lstat(ptr->content, &stat) < 0)
			break ;
		len += stat.st_blocks / 2;
		ptr = ptr->next;
	}
	printf("total %d\n", len);
	return (0);
}
