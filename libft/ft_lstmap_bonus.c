/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:49:50 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/25 13:49:51 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Mallocs a new list where f(lst->content) is successful
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*temp;
	t_list	*cursor;
	t_list	*node_add;
	t_list	*out;

	if (!lst || !f || !del)
		return (NULL);
	out = NULL;
	cursor = lst;
	while (cursor)
	{
		temp = f(cursor->content);
		node_add = ft_lstnew(temp);
		if (!node_add)
		{
			del(temp);
			ft_lstclear(&out, del);
			return (NULL);
		}
		ft_lstadd_back(&out, node_add);
		cursor = cursor->next;
	}
	return (out);
}
