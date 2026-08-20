/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:37:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:42:48 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "types.h"
#include "util/cones.h"
#include "util/cylinders.h"
#include "util/intersections.h"

/**
 * @brief Find sphere intersects
 * 
 * @param sphere 
 * @param ray 
 * @return t_intersects 
 */
t_intersects	intersect_sphere(t_sphere *sphere, t_ray ray)
{
	t_intersects	result;
	t_ray			local_ray;
	t_tuple			sphere_to_ray;
	double			abc[3];
	double			discriminant;

	result = intersections_create();
	local_ray = transform(ray, sphere->inverse);
	sphere_to_ray = tuples_sub(local_ray.origin, point(0.0, 0.0, 0.0));
	abc[0] = dot_product(local_ray.dir, local_ray.dir);
	abc[1] = 2 * dot_product(local_ray.dir, sphere_to_ray);
	abc[2] = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return (result);
	result = intersections_add(result, create_intersection(SPHERE,
				(void *)sphere, (-abc[1] - sqrt(discriminant))
				/ (2 * abc[0])));
	result = intersections_add(result, create_intersection(SPHERE,
				(void *)sphere, (-abc[1] + sqrt(discriminant))
				/ (2 * abc[0])));
	return (result);
}

/**
 * @brief Adds a hit to the xs depending on height bounds by cylinder
 * and cone, and add the last double from the array to the xs intersections
 * 
 * @param obj 
 * @param bounds_t 
 * @param r 
 * @param xs 
 */
static void	add_hit(t_object obj, double bounds_t[3], t_ray r,
				t_intersects *xs)
{
	double	y;

	y = r.origin.y + bounds_t[2] * r.dir.y;
	if (bounds_t[0] < y && y < bounds_t[1])
		*xs = intersections_add(*xs, create_intersection(obj.type, obj.ptr,
					bounds_t[2]));
}

/**
 * @brief Finds the intersects of a cylinder
 * 
 * @param cyl 
 * @param ray 
 * @return t_intersects 
 */
t_intersects	intersect_cylinder(t_cylinder *cyl, t_ray ray)
{
	double			abc[3];
	double			disc;
	double			t[2];
	t_intersects	xs;

	ray = transform(ray, cyl->transform);
	abc[0] = pow(ray.dir.x, 2.0) + pow(ray.dir.z, 2.0);
	if (abc[0] < UNIT_EPSILON)
		return (xs = intersections_create(), intersect_caps(cyl, ray, &xs), xs);
	abc[1] = (2 * ray.origin.x * ray.dir.x) + (2 * ray.origin.z * ray.dir.z);
	abc[2] = pow(ray.origin.x, 2.0) + pow(ray.origin.z, 2.0) - 1;
	disc = pow(abc[1], 2.0) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (intersections_create());
	t[0] = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
	xs = intersections_create();
	add_hit((t_object){CYLINDER, cyl},
		(double [3]){cyl->min, cyl->max, t[0]}, ray, &xs);
	add_hit((t_object){CYLINDER, cyl},
		(double [3]){cyl->min, cyl->max, t[1]}, ray, &xs);
	return (intersect_caps(cyl, ray, &xs), xs);
}

/**
 * @brief Cone intersect extension, finding hits and proceding
 * 
 * @param cone 
 * @param ray 
 * @param abc 
 * @param xs 
 */
static void	intersect_cone_quad(t_cone *cone, t_ray ray, double abc[3],
				t_intersects *xs)
{
	double	disc;
	double	t[2];

	disc = pow(abc[1], 2.0) - (4 * abc[0] * abc[2]);
	if (disc < 0)
	{
		intersect_caps_cone(cone, ray, xs);
		return ;
	}
	t[0] = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	t[1] = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	if (t[0] > t[1])
		ft_swap(&t[0], &t[1]);
	add_hit((t_object){CONE, cone},
		(double [3]){cone->min, cone->max, t[0]}, ray, xs);
	add_hit((t_object){CONE, cone},
		(double [3]){cone->min, cone->max, t[1]}, ray, xs);
	intersect_caps_cone(cone, ray, xs);
}

/**
 * @brief Finds the intersections of a cone
 * 
 * @param cone 
 * @param ray 
 * @return t_intersects 
 */
t_intersects	intersect_cone(t_cone *cone, t_ray ray)
{
	double			abc[3];
	t_intersects	xs;

	ray = transform(ray, cone->transform);
	abc[0] = pow(ray.dir.x, 2.0) - pow(ray.dir.y, 2.0) + pow(ray.dir.z, 2.0);
	abc[1] = (2 * ray.origin.x * ray.dir.x) - (2 * ray.origin.y * ray.dir.y)
		+ (2 * ray.origin.z * ray.dir.z);
	abc[2] = pow(ray.origin.x, 2.0) - pow(ray.origin.y, 2.0)
		+ pow(ray.origin.z, 2.0);
	xs = intersections_create();
	if (fabs(abc[0]) < UNIT_EPSILON)
	{
		if (fabs(abc[1]) < UNIT_EPSILON)
			return (intersect_caps_cone(cone, ray, &xs), xs);
		add_hit((t_object){CONE, cone},
			(double [3]){cone->min, cone->max, -abc[2] / abc[1]}, ray, &xs);
		return (intersect_caps_cone(cone, ray, &xs), xs);
	}
	intersect_cone_quad(cone, ray, abc, &xs);
	return (xs);
}
