/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:29:42 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 12:29:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*result;
	size_t	len;

	len = ft_strlen(s);
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	return (ft_memmove(result, s, len + 1));
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printcs(argv[1], strlen(argv[1]));
		printcs(ft_strdup(argv[1]), strlen(argv[1]));
		printcs(strdup(argv[1]), strlen(argv[1]));
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
