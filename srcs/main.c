/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:39:37 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/25 03:29:57 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	init_opts(va_list args, char opt) {
    t_ls *st = va_arg(args, t_ls *);

	switch (opt) {
		case 'l':
			st->opts.l = true;
			break;
		case 'R':
			st->opts.ur = true;
			break;
		case 'a':
			st->opts.a = true;
			break;
		case 'r':
			st->opts.r = true;
			break;
		case 't':
			st->opts.t = true;
			break;
	}
}

bool	ft_ls2(t_opts *opts, t_list *ptr) {
	t_stat		st;

	while (ptr) {
		if (lstat(ptr->content, &st) == -1)
			return (error((char *)ptr->content));
		if (S_ISDIR(st.st_mode))
			open_dir(opts, ptr->content);
		ptr = ptr->next;
	}
	return (false);
}

bool	ft_ls(t_ls *ls, char **av, int ac) {
	t_list	*ptr;
	int		i;

	ptr = NULL;
	i = 0;
	while (++i < ac) {
		if (av[i][0] != '-')
			ft_lstadd_back(&ptr, ft_lstnew(av[i]));
	}
	if (!ptr)
		ptr = ft_lstnew(".");
	return (ft_ls2(&ls->opts, sortlist(&ptr, &ls->opts)));
}

int		main(int ac, char **av) {
	t_ls		ls;
	t_args		mappings[] = {
        { 'l', init_opts },
        { 'R', init_opts },
        { 'a', init_opts },
        { 'r', init_opts },
        { 't', init_opts }
    };
    t_argsArray args = {
        .mappings = mappings,
        .len = sizeof(mappings) / sizeof(mappings[0])
    };
	ft_bzero(&ls, sizeof(ls));
	for (int i = 1; i < ac; i++) {
        ft_parseargs(args, av[i], &ls);
    }
	return (ft_ls(&ls, av, ac));
}