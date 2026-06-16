/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:58:54 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/24 21:58:56 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Function that returns last node of list
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*cursor;

	if (!lst)
		return (NULL);
	cursor = lst;
	while (cursor->next)
		cursor = cursor->next;
	return (cursor);
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

	cursor = ft_lstlast(node1);
	printf("Last element: %s\n", (char *)cursor->content);
}
*/
