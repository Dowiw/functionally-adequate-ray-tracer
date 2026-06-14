/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 00:04:21 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/22 00:04:23 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Helper function that helps count number of strings in s
static size_t	count_str(char const *s, char c)
{
	size_t	out;

	out = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			out++;
		while (*s && *s != c)
			s++;
	}
	return (out);
}

//Helper function that puts string into out[i] from its index start to its end
static char	*dup_str(const char *start, const char *end)
{
	char	*string;
	size_t	len;

	len = (size_t)end - (size_t)start;
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	ft_memcpy(string, start, len);
	string[len] = '\0';
	return (string);
}

//Helper function to fill array
static int	fill_array(char **out, const char *s, char c)
{
	size_t		i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			out[i] = dup_str(start, s);
			if (!out[i])
			{
				while (i--)
					free(out[i]);
				return (0);
			}
			i++;
		}
	}
	out[i] = NULL;
	return (1);
}

/**
 * @brief Splits str s into a mallocated array of strings based on delimiter c
 * @return Splitted string. NULL if malloc errors or invalid string.
 */
char	**ft_split(char const *s, char c)
{
	char	**out;

	if (!s)
		return (NULL);
	out = malloc(sizeof(char *) * (count_str(s, c) + 1));
	if (!out)
		return (NULL);
	if (!fill_array(out, s, c))
	{
		free(out);
		return (NULL);
	}
	return (out);
}

/*
int main(void)
{
	#include <stdio.h>
	char *test = "Hello,Hi,Hello";
	char **test_out = ft_split(test, ',');
	for (int i = 0; i < 3; i++)
	{
		printf("%s\n", test_out[i]);
		free(test_out[i]);
	}
	free(test_out);
	return (0);
}
*/
