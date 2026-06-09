/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:49 by sstark            #+#    #+#             */
/*   Updated: 2025/05/14 14:16:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_calculate_splits(char const *s, char c);

static char		**ft_populate_splits(char **result, char const *s, char c);

static char		*ft_copy_split(char const *s, size_t from, size_t to);

static char		**ft_free_splits(char **result, size_t size);

// The question doesn't specify behaviour regarding empty strings:
//   - Should ft_split("", 'e') return NULL, an empty array
//     or a singleton array with an empty string?
//   - Should ft_split("eee", 'e') return NULL, an empty array
//     or an array with only empty strings and how many?
//
//    -> In this implementation, an empty array is returned.
char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	splits;

	splits = ft_calculate_splits(s, c);
	result = malloc((splits + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	return (ft_populate_splits(result, s, c));
}

static size_t	ft_calculate_splits(char const *s, char c)
{
	size_t	splits;
	int		in_split;
	size_t	i;

	splits = 0;
	in_split = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!in_split && s[i] != c)
			splits++;
		in_split = s[i] != c;
		i++;
	}
	return (splits);
}

static char	**ft_populate_splits(char **result, char const *s, char c)
{
	int		in_split;
	size_t	from;
	size_t	i;
	size_t	j;

	in_split = 0;
	from = 0;
	i = 0;
	j = 0;
	while (i == 0 || s[i - 1] != '\0')
	{
		if (in_split && (s[i] == c || s[i] == '\0'))
		{
			result[j] = ft_copy_split(s, from, i);
			if (result[j] == NULL)
				return (ft_free_splits(result, j));
			j++;
		}
		if (!in_split && s[i] != c)
			from = i;
		in_split = s[i] != c;
		i++;
	}
	result[j] = NULL;
	return (result);
}

static char	*ft_copy_split(char const *s, size_t from, size_t to)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = to - from;
	result = malloc(len + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[from + i];
		i++;
	}
	result[len] = '\0';
	return (result);
}

static char	**ft_free_splits(char **result, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		free(result[i]);
		result[i] = NULL;
	}
	free(result);
	return (NULL);
}

/*
#include <stdio.h>
#include <ctype.h>
#include <bsd/string.h>
static void	printcs(char *str, int len);
int	main(int argc, char **argv)
{
	char	**result;
	size_t	i;

	if (argc == 3)
	{
		result = ft_split(argv[1], argv[2][0]);
		if (result == NULL)
		{
			printf("NULL");
			return (0);
		}
		i = 0;
		while (result[i] != NULL)
		{
			printcs(result[i], strlen(result[i]));
			printf("\n");
			i++;
		}
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
