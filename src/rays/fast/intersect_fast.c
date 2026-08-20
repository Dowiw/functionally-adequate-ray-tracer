/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_fast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:25 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:43:03 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stddef.h>
#include "minirt.h"
#include "ray.h"
#include "util/intersections.h"

t_intersect	intersect_scene_and_hit(t_scene *scene, t_ray ray)
{
	t_intersect	result;
	int			i;

	result.t = -1.0;
	result.obj.type = SPHERE;
	result.obj.ptr = NULL;
	i = 0;
	while (scene->spheres[i] != NULL)
		intersect_sphere_fast(scene->spheres[i++], ray, &result);
	i = 0;
	while (scene->planes[i] != NULL)
		intersect_plane_fast(scene->planes[i++], ray, &result);
	i = 0;
	while (scene->cylinders[i] != NULL)
		intersect_cylinder_fast(scene->cylinders[i++], ray, &result);
	i = 0;
	while (scene->cones[i] != NULL)
		intersect_cone_fast(scene->cones[i++], ray, &result);
	return (result);
}
