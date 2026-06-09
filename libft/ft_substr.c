/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:51:17 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:51:19 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	i = 0;
	while (s[i] != '\0' && i < start + len)
		i++;
	if (start > i)
		start = i;
	len = i - start;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	if (argc == 4)
		printcs(ft_substr(argv[1], atoi(argv[2]), atoi(argv[3])), atoi(argv[3]));
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
