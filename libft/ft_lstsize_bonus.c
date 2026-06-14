/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:45:32 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/24 21:45:35 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cursor;

	if (!lst)
		return (0);
	i = 1;
	cursor = lst;
	while (cursor->next != NULL)
	{
		i++;
		cursor = cursor->next;
	}
	return (i);
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

	printf("Size of list1: %i", ft_lstsize(node1));
	printf("Size of list1: %i", ft_lstsize(NULL));
}
*/
