/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 06:04:47 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 06:24:58 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	get_st_nlink_max(t_list *ptr) {
	t_stat	st;
	int		max;

	max = 0;
	while (ptr) {
		if (lstat(ptr->content, &st) < 0)
			break ;
		if (st.st_nlink <= 9 && max <= 1)
			max = 1;
		else if (st.st_nlink <= 99 && max <= 2)
			max = 2;
		else if (st.st_nlink <= 999 && max <= 3)
			max = 3;
		ptr = ptr->next;
	}
	return (max);
}

int	get_st_size_max(t_list *ptr) {
	t_stat	st;
	int		max;

	max = 0;
	while (ptr) {
		if (lstat(ptr->content, &st) < 0)
			break ;
		if (st.st_size <= 9 && max <= 1)
			max = 1;
		else if (st.st_size <= 99 && max <= 2)
			max = 2;
		else if (st.st_size <= 999 && max <= 3)
			max = 3;
		else if (st.st_size <= 9999 && max <= 4)
			max = 4;
		else if (st.st_size <= 99999 && max <= 5)
			max = 5;
		else if (st.st_size <= 999999 && max <= 6)
			max = 6;
		else if (st.st_size <= 9999999 && max <= 7)
			max = 7;
		else if (st.st_size <= 99999999 && max <= 8)
			max = 8;
		else if (st.st_size <= 999999999 && max <= 9)
			max = 9;
		ptr = ptr->next;
	}
	return (max);
}