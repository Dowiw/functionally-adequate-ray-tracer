/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:26:44 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 16:00:13 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"
#include "util/intersections.h"

/**
 * @brief Returns a ray that starts at the camera and passes through 
 * the given pixel on the canvas.
 *
 * @param camera
 * @param x
 * @param y
 * @return t_ray
 */
t_ray	ray_for_pixel(t_camera camera, int x, int y)
{
	double	x_offset;
	double	y_offset;
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	x_offset = (x + 0.5) * camera.pixel_size;
	y_offset = (y + 0.5) * camera.pixel_size;
	world_x = camera.half_width - x_offset;
	world_y = camera.half_height - y_offset;
	pixel = matrix4x4_multiply_tuple(camera.inverse, point(world_x, world_y, -1.0));
	origin = matrix4x4_multiply_tuple(camera.inverse, point(0.0, 0.0, 0.0));
	direction = calc_norm(tuples_sub(pixel, origin));
	return ((t_ray){origin, direction});
}

// TODO: handle different object types
/**
 * @brief Precomputes a few values and stores them in the returned t_comps for ease of use.
 *
 * @param ray
 * @param hit
 * @return t_comps
 */
t_comps	prepare_computations(t_ray ray, t_intersection *hit)
{
	t_comps	result;

	result.t = hit->t;
	result.obj = hit->obj;
	result.point = position(ray, hit->t);
	result.eyev = tuple_neg(ray.direction);
	result.normalv = normal_at(&result.obj, result.point);
	result.inside = dot_product(result.normalv, result.eyev) < 0.0;
	if (result.inside)
		result.normalv = tuple_neg(result.normalv);
	result.over_point = tuples_add(result.point, tuple_mult(result.normalv, UNIT_EPSILON));
	return (result);
}

static t_material	get_material(t_object obj)
{
	if (obj.type == SPHERE)
		return (((t_sphere *)obj.object)->material);
	else if (obj.type == PLANE)
		return (((t_plane *)obj.object)->material);
	else if (obj.type == CYLINDER)
		return (((t_cylinder *)obj.object)->material);
	return (material());
}

/**
 * @brief Calculates the color at the intersection represented by the given comps.
 *
 * @param scene
 * @param comps
 * @return t_color
 */
t_color	shade_hit(t_scene *scene, t_comps comps)
{
	int			shadowed;
	t_material	mat;

	mat = get_material(comps.obj);
	shadowed = is_shadowed(*scene, comps.over_point);
	return (lighting(mat,
			scene->light,
			comps.point,
			comps.eyev,
			comps.normalv,
			shadowed));
}

/**
 * @brief Calculates the color at the intersection of the given ray in the scene.
 *        Returns black if the ray doesn't intersect with any objects.
 *
 * @param scene
 * @param ray
 * @return t_color
 */
t_color	color_at(t_scene *scene, t_ray ray)
{
	t_intersections	xs;
	t_intersection	*hit;
	t_comps			comps;
	t_color			res;

	xs = intersect_scene(scene, ray);
	hit = intersect_hit(xs);
	if (hit == NULL)
	{
		free_intersections(xs);
		return (color_black());
	}
	comps = prepare_computations(ray, hit);
	res = shade_hit(scene, comps);
	free_intersections(xs);
	return (res);
}
