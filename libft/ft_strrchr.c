/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 13:27:12 by sstark            #+#    #+#             */
/*   Updated: 2025/05/09 13:51:05 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*result;
	int		i;

	result = NULL;
	i = 0;
	while (i == 0 || s[i - 1] != '\0')
	{
		if (((unsigned char *) s)[i] == (unsigned char) c)
			result = (char *) &s[i];
		i++;
	}
	return (result);
}

/*
#include <stdio.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	if (argc == 3)
	{
		printf("%s\n", ft_strrchr(argv[1], argv[2][0]));
		printf("%s\n", strrchr(argv[1], argv[2][0]));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
