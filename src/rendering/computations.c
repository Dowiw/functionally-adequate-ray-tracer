/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:26:44 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 17:28:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"

t_ray	ray_for_pixel(t_camera camera, int x, int y)
{
	double	x_offset = (x + 0.5) * camera.pixel_size;
	double	y_offset = (y + 0.5) * camera.pixel_size;

	double	world_x = camera.half_width - x_offset;
	double	world_y = camera.half_height - y_offset;

	t_tuple pixel = matrix4x4_multiply_tuple(matrix4x4_inverse(camera.transform), point(world_x, world_y, -1.0));
	t_tuple origin = matrix4x4_multiply_tuple(matrix4x4_inverse(camera.transform), point(0.0, 0.0, 0.0));
	t_tuple direction = calc_norm(tuples_sub(pixel, origin));

	return ((t_ray){origin, direction});
}

// TODO: handle different object types
t_comps	prepare_computations(t_ray ray, t_intersection *hit)
{
	t_comps	result;

	result.t = hit->t;
	result.obj = hit->obj;
	result.point = position(ray, hit->t);
	result.eyev = tuple_neg(ray.direction);
	result.normalv = normal_at((t_sphere *) result.obj.object, result.point);
	result.inside = dot_product(result.normalv, result.eyev) < 0.0;
	if (result.inside)
		result.normalv = tuple_neg(result.normalv);
	return (result);
}

// TODO: handle different object types
t_color shade_hit(t_scene *scene, t_comps comps)
{
	return (lighting(((t_sphere *) comps.obj.object)->material, scene->light, comps.point, comps.eyev, comps.normalv));
}

t_color	color_at(t_scene *scene, int x, int y)
{
	t_ray			ray;
	t_intersection	*hit;
	t_comps			comps;

	ray = ray_for_pixel(scene->camera, x, y);
	hit = intersect_hit(intersect_scene(scene, ray));
	if (hit == NULL)
		return (color_black());
	comps = prepare_computations(ray, hit);
	return (shade_hit(scene, comps));
}
