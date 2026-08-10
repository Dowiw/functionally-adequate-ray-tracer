/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:34:09 by sstark            #+#    #+#             */
/*   Updated: 2026/08/10 17:06:23 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"
#include "util/arrays.h"

t_intersections	intersections_create(void)
{
	t_intersections	xs;

	xs.list = (t_intersection **) array_create();
	xs.count = 0;
	return (xs);
}

t_intersections	intersections_add(t_intersections xs, t_intersection *intersection)
{
	xs.list = (t_intersection **) array_add((void **) xs.list, (void *) intersection);
	xs.count = array_len((void **) xs.list);
	return (xs);
}

t_intersections	intersections_add_all(t_intersections xs, t_intersections to_add)
{
	xs.list = (t_intersection **) array_add_all((void **) xs.list, (void **) to_add.list);
	if (to_add.list != NULL)
		free(to_add.list);
	xs.count = array_len((void **) xs.list);
	return (xs);
}

int	intersections_len(t_intersections xs)
{
	return (xs.count);
}

void	free_intersections(t_intersections xs)
{
	free_array((void **) xs.list);
}
