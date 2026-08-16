/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:43:23 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 15:53:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

/**
 * @brief Plane constructor with default values.
 * 
 * Position: 0, 0, 0
 * Vector: 0, 1, 0
 * Transform: Identity
 * Material: material()
 * 
 * @return t_plane plane with the values
 */
t_plane	plane_create(void)
{
	t_plane	p;

	p.material = material();
	p.transform = matrix4x4_identity();
	p.inverse = matrix4x4_identity();
	p.pos = point(0, 0, 0);
	p.vec = vector(0, 1, 0);
	return (p);
}

/**
 * @brief Initialize the planes array.
 * array[0] = NULL and count = 0.
 * 
 * @return t_plane** planes array
 */
t_plane	**planes_create(void)
{
	return ((t_plane **) array_create());
}

t_plane	**planes_add(t_plane **array, t_plane *plane)
{
	return ((t_plane **) array_add((void **) array, (void *) plane));
}

int	planes_len(t_plane **array)
{
	return (array_len((void **) array));
}

void	free_planes(t_plane **array)
{
	free_array((void **) array);
}
