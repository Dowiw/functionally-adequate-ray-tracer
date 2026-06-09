/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:57:48 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 11:57:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
			return ((void *) &s[i]);
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("%s\n", (char *) ft_memchr(argv[1], argv[2][0], atoi(argv[3])));
		printf("%s\n", (char *) memchr(argv[1], argv[2][0], atoi(argv[3])));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
