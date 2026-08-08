/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:34:09 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 10:52:21 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

t_intersection	**intersections_create(void)
{
	return ((t_intersection **) array_create());
}

t_intersection	**intersections_add(t_intersection **array, t_intersection *intersection)
{
	return ((t_intersection **) array_add((void **) array, (void *) intersection));
}

t_intersection	**intersections_add_all(t_intersection **array, t_intersection **intersections)
{
	return ((t_intersection **) array_add_all((void **) array, (void **) intersections));
}

int	intersections_len(t_intersection **array)
{
	return (array_len((void **) array));
}

void	free_intersections(t_intersection **array)
{
	free_array((void **) array);
}
