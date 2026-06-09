/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:51:43 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:51:44 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strcontains(char const *s, char c);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	from;
	size_t	to;

	from = 0;
	while (s1[from] != '\0' && ft_strcontains(set, s1[from]))
		from++;
	to = ft_strlen(s1);
	while (to > from && ft_strcontains(set, s1[to - 1]))
		to--;
	result = malloc(to - from + 1);
	if (result == NULL)
		return (NULL);
	ft_memcpy(result, s1 + from, to - from);
	result[to - from] = '\0';
	return (result);
}

static int	ft_strcontains(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	char	*result;
	if (argc == 3)
	{
		result = ft_strtrim(argv[1], argv[2]);
		printcs(result, strlen(result));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}

static void	printc(char c)
{
	if (c == '\0')
		printf("_");
	else if (!isprint(c))
		printf("?");
	else
		printf("%c", c);
}

static void	printcs(char *str, int len)
{
	int	i;

	i = -3;
	while (i < 0)
		printc(str[i++]);
	printf("|");
	while (i < len + 1)
		printc(str[i++]);
	printf("|");
	while (i < len + 4)
		printc(str[i++]);
	printf("\n");
}
*/
