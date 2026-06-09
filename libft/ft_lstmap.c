/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 18:23:26 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 18:23:27 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*e;

	if (lst == NULL)
		return (NULL);
	result = ft_lstnew(f(lst->content));
	if (result == NULL)
		return (NULL);
	e = result;
	lst = lst->next;
	while (lst != NULL)
	{
		e->next = ft_lstnew(f(lst->content));
		if (e->next == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		e = e->next;
		lst = lst->next;
	}
	return (result);
}

/*
#include <stdio.h>
#include <ctype.h>
static void	ft_createlst(t_list **lst, char **strs, size_t size);
static void	ft_printlst(t_list *lst);
static void	*ft_map(void *content);
static void	ft_del(void *content);
int	main(int argc, char **argv)
{
	t_list	*lst;

	if (argc >= 1)
	{
		lst = NULL;
		ft_createlst(&lst, argv + 1, argc - 1);
		ft_printlst(lst);
		lst = ft_lstmap(lst, &ft_map, &ft_del);
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

static char	ft_mapc(unsigned int i, char c)
{
	(void) i;
	return (toupper(c));
}

static void	*ft_map(void *content)
{
	printf("mapping \"%s\"\n", (char *) content);
	return (ft_strmapi((char *) content, &ft_mapc));
}

static void	ft_del(void *content)
{
	printf("deleting \"%s\"\n", (char *) content);
}
*/
