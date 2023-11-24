/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:40:26 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 06:26:19 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

bool	open_dir(t_opts *opts, char *directory) {
	DIR				*dir;
	struct dirent	*file;
	t_list			*ptr;
	char			*name;
	int				st_nlink;
	int				st_size;

	ptr = NULL;
	print_dirname(opts, directory);
	if (!(dir = opendir(directory))) {
		printf("ft_ls: %s: %s\n", directory, strerror(errno));
		return (true);
	}
	while ((file = readdir(dir))) {
		name = ft_strjoin(directory, "/");
		name = ft_strjoin_free(name, file->d_name);
		if (file->d_name[0] != '.' || opts->a)
			ft_lstadd_back(&ptr, ft_lstnew(name));
	}
	if (closedir(dir) == -1) {
		printf("ft_ls: %s: %s\n", directory, strerror(errno));
		return (true);
	}
	st_nlink = get_st_nlink_max(ptr);
	st_size = get_st_size_max(ptr);
	print_total(ptr, opts);
	display(opts, sortlist(ptr, opts), st_nlink, st_size);
	if (opts->ur)
		ft_ls2(opts, sortlist(ptr, opts));
	//TODO: free list
	return (0);
}
