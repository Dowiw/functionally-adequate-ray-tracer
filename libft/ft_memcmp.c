/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:26:40 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 12:26:48 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *) s1)[i] != ((unsigned char *) s2)[i])
			return (((unsigned char *) s1)[i] - ((unsigned char *) s2)[i]);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	if (argc == 4)
	{
		printf("%d\n", ft_memcmp(argv[1], argv[2], (size_t) atoi(argv[3])));
		printf("%d\n", memcmp(argv[1], argv[2], (size_t) atoi(argv[3])));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
