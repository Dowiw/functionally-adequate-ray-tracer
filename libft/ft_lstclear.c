/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:09 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 18:23:10 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*e;
	t_list	*next;

	e = *lst;
	while (e != NULL)
	{
		next = e->next;
		ft_lstdelone(e, del);
		e = next;
	}
	*lst = NULL;
}

/*
#include <stdio.h>
static void	ft_createlst(t_list **lst, char **strs, size_t size);
static void	ft_printlst(t_list *lst);
static void	ft_del(void *content);
int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc >= 2)
	{
		lst = NULL;
		ft_createlst(&lst, argv + 1, argc - 1);
		ft_printlst(lst);
		ft_lstclear(&lst, &ft_del);
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

static void	ft_del(void *content)
{
	printf("deleting \"%s\"\n", (char *) content);
}
*/
