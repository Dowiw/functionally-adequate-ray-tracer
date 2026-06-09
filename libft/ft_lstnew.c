/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:21:50 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 18:21:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (lst == NULL)
		return (NULL);
	lst->next = NULL;
	lst->content = content;
	return (lst);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 0)
		printf("No tests for %s: Used by all t_list tests.\n", argv[0]);
	return (0);
}
*/
