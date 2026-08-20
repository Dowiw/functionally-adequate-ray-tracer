/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:43:35 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:42:30 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "util/arrays.h"

/**
 * @brief Create a default sphere struct.
 * View function for more information.
 *
 * @return t_sphere sphere struct with default values
 */
t_sphere	sphere_create(void)
{
	t_sphere	sphere;

	sphere.pos = (t_point){0, 0, 0, POINT};
	sphere.transform = m4x4_identity();
	sphere.inverse = m4x4_identity();
	sphere.d = 2.0;
	sphere.material = material();
	return (sphere);
}

/**
 * @brief Creates an empty sphere array
 *
 * @return t_sphere** empty
 */
t_sphere	**spheres_create(void)
{
	return ((t_sphere **)array_create());
}

t_sphere	**spheres_add(t_sphere **array, t_sphere *sphere)
{
	return ((t_sphere **)array_add((void **)array, (void *)sphere));
}

/**
 * @brief Counts the number of spheres in a NULL-terminated array.
 *
 * @param arr the array to measure
 * @return the number of elements
 */
int	spheres_len(t_sphere **array)
{
	return (array_len((void **)array));
}

/**
 * @brief Frees an array of sphere pointers and the array itself.
 *
 * @param arr the array to free
 */
void	free_spheres(t_sphere **array)
{
	free_array((void **)array);
}
