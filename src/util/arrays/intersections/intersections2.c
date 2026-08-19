/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:08:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "scene.h"
#include "util/arrays.h"

int		intersections_compare(t_intersect *a, t_intersect *b)
{
	if (a->t > b->t)
		return (1);
	if (a->t < b->t)
		return (-1);
	return (0);
}

void	intersections_sort(t_intersects *xs)
{
	if (xs != NULL && xs->list != NULL)
		arrays_sort((void **) xs->list, (int (*)(void *, void *)) &intersections_compare);
}
