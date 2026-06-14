/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:29:48 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/23 13:29:49 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Applies function (*f) to characters of (*s) and stores results to new (char *)
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*out;
	unsigned int	i;
	unsigned int	s_len;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	out = malloc(sizeof(char) * (s_len + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (i < s_len)
	{
		out[i] = (*f)(i, s[i]);
		i++;
	}
	out[i] = '\0';
	return (out);
}

/*
char test_f(unsigned int i, char c)
{
	return (c + i);
}

int main(void)
{
	#include <stdio.h>
	char *test = ft_strmapi("abcdef", test_f);
	printf("%s\n", test);
	free(test);
	return (0);
}
*/
