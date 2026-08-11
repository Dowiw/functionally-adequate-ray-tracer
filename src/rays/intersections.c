/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:37:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/10 17:06:23 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "util/intersections.h"

/**
 * @brief Allocates and initializes an intersection
 *
 * @param the type of object to be intersected
 * @param the object
 * @param time
 * @return t_intersection*
 */
t_intersection	*create_intersection(enum e_object_type type, void *object, double t)
{
	t_intersection	*result;

	result = malloc(sizeof(t_intersection));
	if (result == NULL)
		return (NULL);
	result->obj.type = type;
	result->obj.object = object;
	result->t = t;
	return (result);
}

/**
 * @brief Calculates where the ray intersects the sphere and returns an array of intersections
 *
 * @param sphere
 * @param ray
 * @return t_intersection**
 */
t_intersections	intersect_sphere(t_sphere *sphere, t_ray ray)
{
	t_intersections	result;
	t_ray			local_ray;
	t_tuple			sphere_to_ray;
	double			abc[3];
	double			discriminant;

	result = intersections_create();
	local_ray = transform(ray, matrix4x4_inverse(sphere->transform));
	sphere_to_ray = tuples_sub(local_ray.origin, point(0.0, 0.0, 0.0));
	abc[0] = dot_product(local_ray.direction, local_ray.direction);
	abc[1] = 2 * dot_product(local_ray.direction, sphere_to_ray);
	abc[2] = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (result);
	result = intersections_add(result, create_intersection(SPHERE, (void *) sphere, (-abc[1] - sqrt(discriminant)) / (2 * abc[0])));
	result = intersections_add(result, create_intersection(SPHERE, (void *) sphere, (-abc[1] + sqrt(discriminant)) / (2 * abc[0])));
	return (result);
}

// t_intersections	intersect_plane(t_plane *plane, t_ray ray)
// {
// 	return (intersections_create());
// }

// t_intersections	intersect_cylinder(t_cylinder *cylinder, t_ray ray)
// {
// 	return (intersections_create());
// }

/**
 * @brief Calculates where the ray intersects any objects in the scene and returns an array of intersections
 *
 * @param scene
 * @param ray
 * @return t_intersections
 */
t_intersections	intersect_scene(t_scene *scene, t_ray ray)
{
	t_intersections	result;
	int				i;

	result = intersections_create();
	if (scene->spheres != NULL)
	{
		i = 0;
		while (scene->spheres[i] != NULL)
		{
			result = intersections_add_all(result, intersect_sphere(scene->spheres[i], ray));
			i++;
		}
	}
	// if (scene->planes != NULL)
	// {
	// 	i = 0;
	// 	while (scene->planes[i] != NULL)
	// 	{
	// 		result = intersections_add_all(result, intersect_plane(scene->planes[i], ray));
	// 		i++;
	// 	}
	// }
	// if (scene->cylinders != NULL)
	// {
	// 	i = 0;
	// 	while (scene->cylinders[i] != NULL)
	// 	{
	// 		result = intersections_add_all(result, intersect_cylinder(scene->cylinders[i], ray));
	// 		i++;
	// 	}
	// }
	intersections_sort(&result);
	return (result);
}

/**
 * @brief Returns the closest intersection, ignoring any that are behind the rays origin (and thus have a negative time)
 *
 * @param intersections
 * @return t_intersection*
 */
t_intersection	*intersect_hit(t_intersections intersections)
{
	t_intersection	*hit;
	int				i;

	hit = NULL;
	if (intersections.list == NULL)
		return (NULL);
	i = 0;
	while (intersections.list[i] != NULL)
	{
		if (intersections.list[i]->t >= 0.0 && (hit == NULL || (intersections.list[i]->t < hit->t)))
			hit = intersections.list[i];
		i++;
	}
	return (hit);
}
