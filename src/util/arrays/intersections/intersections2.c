/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:08:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 14:52:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

int		intersections_compare(t_intersection *a, t_intersection *b)
{
	if (a->t > b->t)
		return (1);
	if (a->t < b->t)
		return (-1);
	return (0);
}

void	intersections_sort(t_intersection **array)
{
	#include <stdio.h>
	arrays_sort((void **) array, (int (*)(void *, void *)) &intersections_compare);
}
