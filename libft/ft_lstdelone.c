/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:22:57 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 18:22:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst != NULL)
	{
		del(lst->content);
		lst->content = NULL;
		lst->next = NULL;
		free(lst);
	}
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 0)
		printf("No tests for %s: Used by ft_lstclear.\n", argv[0]);
	return (0);
}
*/
