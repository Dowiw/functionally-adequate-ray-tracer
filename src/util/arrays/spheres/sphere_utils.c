/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:43:35 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 22:09:32 by kmonjard         ###   ########.fr       */
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

	sphere.center = (t_point){0, 0, 0, POINT};
	sphere.transform = matrix4x4_identity();
	sphere.radius = 1.0;
	sphere.diameter = 0;
	sphere.material = material();
	return (sphere);
}

t_sphere	**spheres_create(void)
{
	return ((t_sphere **)array_create());
}

t_sphere	**spheres_add(t_sphere **array, t_sphere *sphere)
{
	return ((t_sphere **)array_add((void **)array, (void *)sphere));
}

int	spheres_len(t_sphere **array)
{
	return (array_len((void **)array));
}

void	free_spheres(t_sphere **array)
{
	free_array((void **)array);
}
