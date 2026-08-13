/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:54 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "util/arrays.h"

/**
 * @brief Default cylinder.
 * 
 * @return t_cylinder 
 */
t_cylinder	cylinder_create(void)
{
	t_cylinder	c;

	c.center = (t_point){0, 0, 0, POINT};
	c.vec = vector(0, 1, 0);
	c.transform = matrix4x4_identity();
	c.diameter = 2.0;
	c.material = material();
	c.height = 0.0;
	return (c);
}

/**
 * @brief Create a cylinder array with:
 * array[0] = NULL and count = 0.
 * 
 * @return t_cylinder** 
 */
t_cylinder	**cylinders_create(void)
{
	return ((t_cylinder **) array_create());
}

t_cylinder	**cylinders_add(t_cylinder **array, t_cylinder *cylinder)
{
	return ((t_cylinder **) array_add((void **) array, (void *) cylinder));
}

int	cylinders_len(t_cylinder **array)
{
	return (array_len((void **) array));
}

void	free_cylinders(t_cylinder **array)
{
	free_array((void **) array);
}
