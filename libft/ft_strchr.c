/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:09:19 by sstark            #+#    #+#             */
/*   Updated: 2025/05/09 13:26:02 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;

	i = 0;
	while (i == 0 || s[i - 1] != '\0')
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
		{
			return ((char *) &s[i]);
		}
		i++;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("%s\n", ft_strchr(argv[1], argv[2][0]));
		printf("%s\n", strchr(argv[1], argv[2][0]));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
