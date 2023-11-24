/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jode-vri <jode-vri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 06:42:33 by jode-vri          #+#    #+#             */
/*   Updated: 2023/11/24 08:57:29 by jode-vri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void swap(t_list *a, t_list *b) {
    void *temp = a->content;
    a->content = b->content;
    b->content = temp;
}

void bubbleSort(t_list *head) {
    int swapped;
    t_list *ptr1;
    t_list *lptr = NULL;

    // Si la liste est vide ou a un seul élément, elle est déjà triée
    if (head == NULL || head->next == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            char *str1 = (char *)ptr1->content;
            char *str2 = (char *)ptr1->next->content;

            // Comparaison en ignorant la casse
            if (strcasecmp(str1, str2) > 0) {
                swap(ptr1, ptr1->next);
                swapped = 1;
            }

            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

t_list	*sortlist(t_list **ptr, t_opts *opts) {
	if (opts->t) {
		
	} else {
		bubbleSort(*ptr);
	}
	if (opts->r) {
		// ptr = reversesort(ptr);
	}
	return (*ptr);
}