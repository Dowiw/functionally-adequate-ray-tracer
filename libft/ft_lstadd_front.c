/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:21:29 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 18:21:30 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*
#include <stdio.h>
static void	ft_createlst(t_list **lst, char **strs, size_t size);
static void	ft_printlst(t_list *lst);
int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc >= 2)
	{
		lst = NULL;
		ft_createlst(&lst, argv + 1, argc - 2);
		ft_printlst(lst);
		ft_lstadd_front(&lst, ft_lstnew(argv[argc - 1]));
		ft_printlst(lst);
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}

static void	ft_createlst(t_list **lst, char **strs, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		ft_lstadd_back(lst, ft_lstnew(strs[i]));
		i++;
	}
}

static void	ft_printlst(t_list *lst)
{
	if (lst != NULL)
	{
		printf("\"%s\"", (char *) lst->content);
		lst = lst->next;
	}
	while (lst != NULL)
	{
		printf(", \"%s\"", (char *) lst->content);
		lst = lst->next;
	}
	printf("\n");
}
*/
