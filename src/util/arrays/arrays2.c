/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:03:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 11:42:21 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "util/arrays.h"

void	arrays_sort(void **array, int (*compare)(void *, void *))
{
	int		len;
	int		i;
	void	*temp;

	if (array == NULL || compare == NULL)
		return ;
	len = array_len(array);
	if (len < 2)
		return ;
	i = 0;
	while (i < len - 1)
	{
		if (compare(array[i], array[i + 1]) > 0)
		{
			temp = array[i];
			array[i] = array[i + 1];
			array[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}
