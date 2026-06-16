/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:04:55 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 23:27:28 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"

/*
 * Returns true if the contents of 'str1' are equal to 'str2'.
 * Returns true if both strings are NULL and false if only one of them is NULL.
 */
int	string_equals(char *str1, char *str2)
{
	int	i;

	if (str1 == NULL || str2 == NULL)
		return (str1 == str2);
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (str1[i] == str2[i]);
}

/*
 * Returns true if 'str' ends in 'suffix'.
 * Returns false if either string is NULL.
 */
int	string_endswith(char *str, char *suffix)
{
	int	str_len;
	int	suffix_len;

	if (str == NULL || suffix == NULL)
		return (0);
	str_len = ft_strlen(str);
	suffix_len = ft_strlen(suffix);
	if (suffix_len > str_len)
		return (0);
	return (ft_strncmp(str + (str_len - suffix_len), suffix, suffix_len) == 0);
}

/*
 * Checks if 'str' ends in 'suffix' (see string_endswith):
 * If it does:
 *  Creates and returns a new string with the characters of 'str' but with 'suffix' removed.
 *  The given 'str' is freed and should be replaced with the returned result.
 * If it does not:
 *  The given 'str' is returned.
 * Returns 'str' if either string is NULL.
 */
char	*string_remove_suffix(char *str, char *suffix)
{
	char	*result;
	int		len;

	if (str == NULL || suffix == NULL)
		return (str);
	if (!string_endswith(str, suffix))
		return (str);
	len = ft_strlen(str) - ft_strlen(suffix);
	result = malloc(len + 1);
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	ft_memcpy(result, str, len);
	result[len] = '\0';
	free(str);
	return (result);
}
