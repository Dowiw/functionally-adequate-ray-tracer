/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 13:16:26 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/25 13:16:27 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Iterates through lst and applies function f to content
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*cursor;

	if (!lst || !f)
		return ;
	cursor = lst;
	while (cursor != NULL)
	{
		f(cursor->content);
		cursor = cursor->next;
	}
}
