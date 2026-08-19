/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:08:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:50:30 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "types.h"

void	intersections_sort(t_intersects *xs)
{
	int			i;
	t_intersect	*temp;

	if (xs == NULL || xs->list == NULL)
		return ;
	if (xs->count < 2)
		return ;
	i = 0;
	while (i < xs->count - 1)
	{
		if (xs->list[i]->t > xs->list[i + 1]->t)
		{
			temp = xs->list[i];
			xs->list[i] = xs->list[i + 1];
			xs->list[i + 1] = temp;
			i = 0;
			continue ;
		}
		i++;
	}
}
