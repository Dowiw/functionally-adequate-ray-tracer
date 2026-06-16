/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:05:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/24 22:05:37 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Adds node new to the end of list
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cursor;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	cursor = *lst;
	while (cursor->next != NULL)
		cursor = cursor->next;
	cursor->next = new;
}

/*
int main(void)
{
	#include <stdio.h>
	#include <string.h>
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

	ft_lstadd_back(list, new);
	cursor = *list;
	while (cursor) {
		printf("List 1 added at end: %s\n", (char *)cursor->content);
		cursor = cursor->next;
	}
}
*/
