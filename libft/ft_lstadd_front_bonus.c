/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:24:29 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/23 20:24:30 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Adds node new to start of list
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

/*
int main(void)
{
	#include <stdio.h>
	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	node1->content = "Hello";

	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	node2->content = "Hi";

	t_list *node3 = (t_list *)malloc(sizeof(t_list));
	node3->content = "Hallo";

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	t_list *cursor = node1;
	while (cursor) {
		printf("List 1: %s\n", (char *)cursor->content);
		cursor = cursor->next;
	}

	t_list **list = &node1;

	t_list *new = (t_list *)malloc(sizeof(t_list));
	new->content = "Bonjour";

	ft_lstadd_front(list, new);
	cursor = new;
	while (cursor) {
		printf("List 1 added at front: %s\n", (char *)cursor->content);
		cursor = cursor->next;
	}
	return (0);
}
*/
