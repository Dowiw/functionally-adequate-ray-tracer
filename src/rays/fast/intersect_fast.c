/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_fast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:25 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 16:28:25 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"

t_intersection	intersect_scene_and_hit(t_scene *scene, t_ray ray)
{
	t_intersection	result;
	int				i;

	result.t = -1.0;
	result.obj.type = SPHERE;
	result.obj.object = NULL;
	i = 0;
	while (scene->spheres[i] != NULL)
	{
		intersect_sphere_fast(scene->spheres[i], ray, &result);
		i++;
	}
	i = 0;
	while (scene->planes[i] != NULL)
	{
		intersect_plane_fast(scene->planes[i], ray, &result);
		i++;
	}
	i = 0;
	while (scene->cylinders[i] != NULL)
	{
		intersect_cylinder_fast(scene->cylinders[i], ray, &result);
		i++;
	}
	return (result);
}
