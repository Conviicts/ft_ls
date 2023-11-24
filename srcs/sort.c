/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:42:33 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 07:04:33 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_list	*asciisort(t_list *ptr) {
	t_list	*current;
	t_list	*tmp;
	char	*tmpstr;

	current = ptr;
	while (current) {
		tmp = current->next;
		while (tmp) {
			if (ft_strcmp(current->content, tmp->content) > 0) {
				tmpstr = current->content;
				current->content = tmp->content;
				tmp->content = tmpstr;
			}
			tmp = tmp->next;
		}
		current = current->next;
	}
	return (ptr);
}

t_list	*sortlist(t_list *ptr, t_opts *opts) {
	// t_stat	st;

	if (opts->t) {
		
	} else {
		ptr = asciisort(ptr);
	}
	if (opts->r) {
		// ptr = reversesort(ptr);
	}
	return (ptr);
}