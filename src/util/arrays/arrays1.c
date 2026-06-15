/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 16:33:04 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:11:27 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libft/libft.h"
#include "util/arrays.h"

/*
 * Creates and returns a NULL-terminated empty array.
 * Returns NULL in case of allocation failure.
 */
void	**array_create(void)
{
	void	**result;

	result = malloc(1 * sizeof(void *));
	if (result == NULL)
		return (NULL);
	result[0] = NULL;
	return (result);
}

/*
 * Creates and returns a NULL-terminated array with the elements of 'array' and adding 'elem' to the end.
 * The given 'array' is freed and should be replaced with the returned result.
 * Returns NULL and frees 'array' (and all its elements) and 'elem' in any of the following cases:
 *  - 'array' or 'elem' is NULL
 *  - allocation failure
 */
void	**array_add(void **array, void *elem)
{
	void	**result;
	int		size;

	if (array == NULL || elem == NULL)
	{
		free_array(array);
		free(elem);
		return (NULL);
	}
	size = array_len(array);
	result = malloc((size + 1 + 1) * sizeof(void *));
	if (result == NULL)
	{
		free_array(array);
		free(elem);
		return (NULL);
	}
	ft_memcpy(result, array, size * sizeof(void *));
	result[size] = elem;
	result[size + 1] = NULL;
	free(array);
	return (result);
}

/*
 * Returns the length of the given 'array'.
 * Returns 0 if 'array' is NULL.
 */
int	array_len(void **array)
{
	int	i;

	if (array == NULL)
		return (0);
	i = 0;
	while (array[i] != NULL)
		i++;
	return (i);
}

/*
 * Frees the given 'array' and all its elements.
 */
void	free_array(void **array)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}
