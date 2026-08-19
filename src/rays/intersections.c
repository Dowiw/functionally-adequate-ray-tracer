/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:37:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/17 10:51:04 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "minirt.h"
#include "scene.h"
#include "libft/libft.h"
#include "util/intersections.h"
#include "util/cylinders.h"
#include "util/cones.h"

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
 * @brief Calculates whether the ray intersects the sphere
 * and returns an array of intersections
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
	local_ray = transform(ray, sphere->inverse);
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

/**
 * @brief Calculates whether the ray intersects a plane.
 * 
 * @param plane 
 * @param ray 
 * @return t_intersections 
 */
t_intersections	intersect_plane(t_plane *plane, t_ray ray)
{
	t_intersections	result;
	t_ray			local_r;
	double			t;

	result = intersections_create();
	local_r = transform(ray, plane->inverse);
	if (fabs(local_r.direction.y) < UNIT_EPSILON)
		return (result);
	t = -local_r.origin.y / local_r.direction.y;
	result = intersections_add(result, create_intersection(PLANE, plane, t));
	return (result);
}

/**
 * @brief Calculates whether a ray intersects a cylinder.
 * 
 * @param cylinder
 * @param ray
 * @return t_intersections
 */
t_intersections	intersect_cylinder(t_cylinder *cylinder, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	double		t0;
	double		t1;
	double		y0;
	double		y1;
	t_intersections	xs;

	a = pow(ray.direction.x, 2.0) + pow(ray.direction.z, 2.0);
	if (a < UNIT_EPSILON)
	{
		xs = intersections_create();
		intersect_caps(cylinder, ray, &xs);
		return (xs);
	}
	b = (2 * ray.origin.x * ray.direction.x) + (2 * ray.origin.z * ray.direction.z);
	c = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - 1;
	disc = pow(b, 2.0) - (4 * a * c);
	if (disc < 0)
		return (intersections_create());
	t0 = (-b - sqrt(disc)) / (2 * a);
	t1 = (-b + sqrt(disc)) / (2 * a);
	if (t0 > t1)
		ft_swap(&t0, &t1);
	xs = intersections_create();
	y0 = ray.origin.y + t0 * ray.direction.y;
	if (cylinder->min < y0 && y0 < cylinder->max)
		xs = intersections_add(xs, create_intersection(CYLINDER, cylinder, t0));
	y1 = ray.origin.y + t1 * ray.direction.y;
	if (cylinder->min < y1 && y1 < cylinder->max)
		xs = intersections_add(xs, create_intersection(CYLINDER, cylinder, t1));
	intersect_caps(cylinder, ray, &xs);
	return (xs);
}

/**
 * @brief Calculates whether a ray intersects a cone.
 * 
 * @param cone
 * @param ray
 * @return t_intersections
 */
t_intersections	intersect_cone(t_cone *cone, t_ray ray)
{
	double			abc[3];
	double			disc;
	double			t[2];
	double			y[2];
	t_intersections	xs;

	abc[0] = pow(ray.direction.x, 2.0) - pow(ray.direction.y, 2.0)
		+ pow(ray.direction.z, 2.0);
	abc[1] = (2 * ray.origin.x * ray.direction.x)
		- (2 * ray.origin.y * ray.direction.y)
		+ (2 * ray.origin.z * ray.direction.z);
	abc[2] = pow(ray.origin.x, 2.0) - pow(ray.origin.y, 2.0)
		+ pow(ray.origin.z, 2.0);
	xs = intersections_create();
	if (fabs(abc[0]) < UNIT_EPSILON)
	{
		if (fabs(abc[1]) < UNIT_EPSILON)
		{
			intersect_caps_cone(cone, ray, &xs);
			return (xs);
		}
		t[0] = -abc[2] / (2 * abc[1]);
		y[0] = ray.origin.y + t[0] * ray.direction.y;
		if (cone->min < y[0] && y[0] < cone->max)
			xs = intersections_add(xs, create_intersection(CONE, cone, t[0]));
		intersect_caps_cone(cone, ray, &xs);
		return (xs);
	}
	disc = pow(abc[1], 2.0) - (4 * abc[0] * abc[2]);
	if (disc < 0)
	{
		intersect_caps_cone(cone, ray, &xs);
		return (xs);
	}
	t[0] = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
	y[0] = ray.origin.y + t[0] * ray.direction.y;
	if (cone->min < y[0] && y[0] < cone->max)
		xs = intersections_add(xs, create_intersection(CONE, cone, t[0]));
	y[1] = ray.origin.y + t[1] * ray.direction.y;
	if (cone->min < y[1] && y[1] < cone->max)
		xs = intersections_add(xs, create_intersection(CONE, cone, t[1]));
	intersect_caps_cone(cone, ray, &xs);
	return (xs);
}

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
	if (scene->planes != NULL)
	{
		i = 0;
		while (scene->planes[i] != NULL)
		{
			result = intersections_add_all(result, intersect_plane(scene->planes[i], ray));
			i++;
		}
	}
	if (scene->cylinders != NULL)
	{
		i = 0;
		while (scene->cylinders[i] != NULL)
		{
			result = intersections_add_all(result, intersect_cylinder(scene->cylinders[i], ray));
			i++;
		}
	}
	if (scene->cones != NULL)
	{
		i = 0;
		while (scene->cones[i] != NULL)
		{
			result = intersections_add_all(result, intersect_cone(scene->cones[i], ray));
			i++;
		}
	}
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
