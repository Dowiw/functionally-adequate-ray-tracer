/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 22:15:44 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/24 22:15:45 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Frees lst and deletes content using del, does not free next node
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst)
		return ;
	del(lst->content);
	free(lst);
}

/*
void	del(void *content)
{
	free(content);
}

int main(void)
{
	#include <stdio.h>
	t_list *node1 = (t_list *)malloc(sizeof(t_list));
	node1->content = ft_strdup("Hello");

	t_list *node2 = (t_list *)malloc(sizeof(t_list));
	node2->content = ft_strdup("Hi");

	t_list *node3 = (t_list *)malloc(sizeof(t_list));
	node3->content = ft_strdup("Hallo");

	node1->next = node2;
	node2->next = node3;
	node3->next = NULL;

	t_list *cursor = node1;
	while (cursor) {
		printf("Before: %s\n", (char *)cursor->content);
		cursor = cursor->next;
	}

	ft_lstdelone(node2, del);
	node1->next = node3;

	cursor = node1;
	while (cursor) {
		printf("After: %s\n", (char *)cursor->content);
		cursor = cursor->next;
	}
	return (0);
}
*/
