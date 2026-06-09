/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:22:13 by sstark            #+#    #+#             */
/*   Updated: 2025/05/07 16:26:12 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	size_t	len;

	if (argc == 3)
	{
		len = strlen(argv[1]);
		printcs(argv[1], len);
		ft_bzero(argv[1], atoi(argv[2]));
		printcs(argv[1], len);
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
