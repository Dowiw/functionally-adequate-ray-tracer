/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:02:55 by sstark            #+#    #+#             */
/*   Updated: 2025/05/07 16:30:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *) s)[i] = c;
		i++;
	}
	return (s);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	char	*s;

	if (argc == 4)
	{
		s = strdup(argv[1]);
		ft_memset(s, argv[2][0], atoi(argv[3]));
		printcs(s, strlen(argv[1]));
		s = strdup(argv[1]);
		memset(s, argv[2][0], atoi(argv[3]));
		printcs(s, strlen(argv[1]));
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
