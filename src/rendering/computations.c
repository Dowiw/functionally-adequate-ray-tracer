/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   computations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:26:44 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 20:22:51 by sstark           ###   ########.fr       */
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
	double	world_x;
	double	world_y;
	t_tuple	pixel;
	t_tuple	origin;
	t_tuple	direction;

	world_x = camera.half_width - (x + 0.5) * camera.pixel_size;
	world_y = camera.half_height - (y + 0.5) * camera.pixel_size;
	pixel = m4x4_multiply_tuple(camera.inverse,
			(t_tuple){world_x, world_y, -1.0, POINT});
	origin = m4x4_multiply_tuple(camera.inverse,
			(t_tuple){0.0, 0.0, 0.0, POINT});
	direction = calc_norm(tuples_sub(pixel, origin));
	return ((t_ray){origin, direction});
}

/**
 * @brief Precomputes a few values and stores them in the returned t_comps
 *
 * @param ray
 * @param hit
 * @return t_comps
 */
t_comps	prepare_computations(t_ray ray, t_intersect *hit)
{
	t_comps	result;

	result.t = hit->t;
	result.obj = hit->obj;
	result.point = position(ray, hit->t);
	result.eyev = tuple_neg(ray.dir);
	result.normalv = normal_at(&result.obj, result.point);
	result.inside = dot_product(result.normalv, result.eyev) < 0.0;
	if (result.inside)
		result.normalv = tuple_neg(result.normalv);
	result.over_point = tuples_add(result.point,
			tuple_mult(result.normalv, UNIT_EPSILON));
	return (result);
}

/**
 * @brief Retrieves the material properties of a generic shape object.
 *
 * @param obj pointer to the intersected object
 * @return the material of the object
 */
static t_material	get_material(t_object obj)
{
	if (obj.type == SPHERE)
		return (((t_sphere *)obj.ptr)->material);
	else if (obj.type == PLANE)
		return (((t_plane *)obj.ptr)->material);
	else if (obj.type == CYLINDER)
		return (((t_cylinder *)obj.ptr)->material);
	else if (obj.type == CONE)
		return (((t_cone *)obj.ptr)->material);
	return (material());
}

/**
 * @brief Calculates the color at the intersection represented by the comps.
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
	return (lighting(mat, *scene, comps, shadowed));
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
	t_intersect	hit;
	t_comps		comps;
	t_color		res;

	hit = intersect_scene_and_hit(scene, ray);
	if (hit.t < 0.0)
		return (color_black());
	comps = prepare_computations(ray, &hit);
	res = shade_hit(scene, comps);
	return (res);
}
