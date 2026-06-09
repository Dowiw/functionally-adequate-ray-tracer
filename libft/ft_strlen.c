/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 15:59:41 by sstark            #+#    #+#             */
/*   Updated: 2025/05/07 16:59:34 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%zu\n", ft_strlen(argv[1]));
		printf("%zu\n", strlen(argv[1]));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
