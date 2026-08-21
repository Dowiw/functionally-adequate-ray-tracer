/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:28:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"

/**
 * @brief Allocates and initializes an intersection
 */
t_intersect	*create_intersection(enum e_shape type, void *o, double t)
{
	t_intersect	*result;

	result = malloc(sizeof(t_intersect));
	if (result == NULL)
		return (NULL);
	result->obj.type = type;
	result->obj.ptr = o;
	result->t = t;
	return (result);
}

/**
 * @brief Generic polymorphic intersect dispatcher
 *
 * @param obj
 * @param ray
 * @return t_intersects
 */
t_intersects	intersect(t_object *obj, t_ray ray)
{
	if (!obj || !obj->ptr)
		return (intersections_create());
	if (obj->type == SPHERE)
		return (intersect_sphere((t_sphere *)obj->ptr, ray));
	else if (obj->type == PLANE)
		return (intersect_plane((t_plane *)obj->ptr, ray));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder((t_cylinder *)obj->ptr, ray));
	else if (obj->type == CONE)
		return (intersect_cone((t_cone *)obj->ptr, ray));
	return (intersections_create());
}

/**
 * @brief Find the intersections of a plane
 * 
 * @param plane 
 * @param ray 
 * @return t_intersects 
 */
t_intersects	intersect_plane(t_plane *plane, t_ray ray)
{
	t_intersects	result;
	t_ray			local_r;
	double			t;

	result = intersections_create();
	local_r = transform(ray, plane->inverse);
	if (fabs(local_r.dir.y) < UNIT_EPSILON)
		return (result);
	t = -local_r.origin.y / local_r.dir.y;
	result = intersections_add(result, create_intersection(PLANE, plane, t));
	return (result);
}

/**
 * @brief Finds the intersections in the scene.
 * 
 * @param scene 
 * @param ray 
 * @return t_intersects 
 */
t_intersects	intersect_scene(t_scene *scene, t_ray ray)
{
	t_intersects	res;
	int				i;

	res = intersections_create();
	i = 0;
	while (scene->spheres && scene->spheres[i])
		res = intersections_add_all(res,
				intersect_sphere(scene->spheres[i++], ray));
	i = 0;
	while (scene->planes && scene->planes[i])
		res = intersections_add_all(res,
				intersect_plane(scene->planes[i++], ray));
	i = 0;
	while (scene->cylinders && scene->cylinders[i])
		res = intersections_add_all(res,
				intersect_cylinder(scene->cylinders[i++], ray));
	i = 0;
	while (scene->cones && scene->cones[i])
		res = intersections_add_all(res,
				intersect_cone(scene->cones[i++], ray));
	intersections_sort(&res);
	return (res);
}

/**
 * @brief Find the intersect closest to the ray.
 * or the hit with the lowest t.
 * 
 * @param intersections 
 * @return t_intersect* 
 */
t_intersect	*intersect_hit(t_intersects intersections)
{
	t_intersect	*hit;
	int			i;

	hit = NULL;
	if (intersections.list == NULL)
		return (NULL);
	i = 0;
	while (intersections.list[i] != NULL)
	{
		if (intersections.list[i]->t >= 0.0 && (hit == NULL
				|| (intersections.list[i]->t < hit->t)))
			hit = intersections.list[i];
		i++;
	}
	return (hit);
}
