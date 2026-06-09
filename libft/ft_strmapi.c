/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:11 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:52:11 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		result[i] = f(i, s[i]);
		i++;
	}
	result[i] = '\0';
	return (result);
}

/*
#include <stdio.h>
#include <ctype.h>
static char	mapping(unsigned int i, char c);
int	main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s\n", ft_strmapi(argv[1], &mapping));
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}

static char	mapping(unsigned int i, char c)
{
	printf("%d: %c\n", i, c);
	return (toupper(c));
}
*/
