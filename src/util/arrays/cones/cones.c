/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:30:00 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 19:42:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "util/arrays.h"
#include <math.h>

/**
 * @brief Default cone initialization.
 *
 * @return t_cone
 */
t_cone	cone_create(void)
{
	t_cone	c;

	c.pos = (t_point){0, 0, 0, POINT};
	c.vec = vector(0, 1, 0);
	c.transform = m4x4_identity();
	c.inverse = m4x4_identity();
	c.d = 2.0;
	c.material = material();
	c.min = -INFINITY;
	c.max = INFINITY;
	c.closed = 0;
	c.height = 0.0;
	return (c);
}

/**
 * @brief Create a cone array.
 *
 * @return t_cone**
 */
t_cone	**cones_create(void)
{
	return ((t_cone **) array_create());
}

t_cone	**cones_add(t_cone **array, t_cone *cone)
{
	return ((t_cone **) array_add((void **) array, (void *) cone));
}

/**
 * @brief Counts the number of cones in a NULL-terminated array.
 *
 * @param arr the array to measure
 * @return the number of elements
 */
int	cones_len(t_cone **array)
{
	return (array_len((void **) array));
}

/**
 * @brief Frees an array of cone pointers and the array itself.
 *
 * @param arr the array to free
 */
void	free_cones(t_cone **array)
{
	free_array((void **) array);
}
