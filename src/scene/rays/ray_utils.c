/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/19 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>

/**
 * @brief Calculate the position of a ray based on time
 * 
 * @param ray ray struct
 * @param time time value
 * @return t_point position of ray after time
 */
t_point	position(t_ray ray, double time)
{
	return (tuples_add(ray.origin, tuple_mult(ray.direction, time)));
}

/**
 * @brief Find the intersections of a ray to a sphere.
 * Most explanations can be found in `./NOTES.md`
 *
 * @param s 
 * @param r 
 * @return t_intersect 
 */
t_intersect	intersect(t_sphere s, t_ray r)
{
	t_intersect	intersection;
	t_tuple		sphere_to_ray;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	sphere_to_ray = tuples_sub(r.origin, s.center);
	a = dot_product(r.direction, r.direction);
	b = 2 * dot_product(r.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2.0) - 4 * a * c;
	if (discriminant < 0)
	{
		intersection.count = 0;
		intersection.times = NULL;
	}
	else
	{
		intersection.count = 2;
		intersection.times = malloc(sizeof(double) * 2);
		if (intersection.times)
		{
			intersection.times[0] = (-b - sqrt(discriminant)) / (2 * a);
			intersection.times[1] = (-b + sqrt(discriminant)) / (2 * a);
		}
	}
	return (intersection);
}

/**
 * @brief Create a single intersection structure.
 * 
 * @param t distance parameter
 * @param obj pointer to the sphere hit
 * @return t_intersection the single intersection structure
 */
t_intersection	intersection(double t, struct s_sphere *obj)
{
	t_intersection	i;

	i.t = t;
	i.obj = obj;
	return (i);
}

/**
 * @brief Aggregate multiple intersections into a single collection structure.
 * 
 * @param count the number of intersections to aggregate
 * @param ... the intersection structures to aggregate
 * @return t_intersections the collection containing the aggregated intersections
 */
t_intersections	intersections(unsigned int count, ...)
{
	va_list			args;
	t_intersections	xs;
	unsigned int	i;

	xs.count = count;
	xs.list = malloc(sizeof(t_intersection) * count);
	if (!xs.list)
	{
		xs.count = 0;
		return (xs);
	}
	va_start(args, count);
	i = 0;
	while (i < count)
	{
		xs.list[i] = va_arg(args, t_intersection);
		i++;
	}
	va_end(args);
	return (xs);
}