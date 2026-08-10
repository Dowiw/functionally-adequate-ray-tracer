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

/**
 * @brief Initialize the intersections structure.
 * 
 * @return t_intersections with NULL in list and 0 in count.
 */
t_intersections	intersections_create(void)
{
	t_intersections	xs;

	xs.list = (t_intersection **) array_create();
	xs.count = 0;
	return (xs);
}

// TODO: exit when malloc fails in checking array_add when it returns NULL
// because of an error and not that there are no intersections
/**
 * @brief Add an intersection to the intersections structure.
 * Specifically, the list.
 * 
 * @param xs intersections containing list and  count
 * @param intersection the intersection to add to the list
 * @return t_intersections with the intersection and incremented count
 */
t_intersections	intersections_add(t_intersections xs, t_intersection *intersection)
{
	xs.list = (t_intersection **) array_add((void **) xs.list, (void *) intersection);
	if (xs.list == NULL)
		xs.count = 0;
	else
		xs.count++;
	return (xs);
}

// TODO: exit when malloc fails in checking array_add_all when add_array
// returns NULL because of a malloc error
/**
 * @brief Add both intersections assuming xs is the main addend.
 * Remember to free the to_add.list afterwards.
 * 
 * @param xs intersections
 * @param to_add intersections
 * @return t_intersections the combined intersection sum
 */
t_intersections	intersections_add_all(t_intersections xs, t_intersections to_add)
{
	xs.list = (t_intersection **) array_add_all((void **) xs.list, (void **) to_add.list);
	if (xs.list == NULL)
		xs.count = 0;
	else
		xs.count += to_add.count;
	return (xs);
}

/**
 * @brief Returns the length of the intersections
 * 
 * @param xs intersections
 * @return int count
 */
int	intersections_len(t_intersections xs)
{
	return (xs.count);
}

/**
 * @brief Frees the intersections structure.
 * Specifically, the xs.list
 * 
 * @param xs intersections
 */
void	free_intersections(t_intersections xs)
{
	free_array((void **) xs.list);
}
