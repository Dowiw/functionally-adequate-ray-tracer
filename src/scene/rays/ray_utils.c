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
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

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
 * @brief Assign time and obj to an intersection struct
 * 
 * @param t time
 * @param obj obj
 * @return t_intersection the struct
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

/**
 * @brief Find the intersections of a ray to a sphere.
 * Most explanations can be found in `./NOTES.md`
 *
 * @param s sphere
 * @param r ray
 * @return t_intersections
 */
t_intersections	intersect(struct s_sphere *s, t_ray r)
{
	t_intersections	intersections;
	t_tuple			sphere_to_ray;
	double			a;
	double			b;
	double			c;
	double			discriminant;
	t_ray			local_ray;

	local_ray = transform(r, matrix4x4_inverse(s->transform));
	sphere_to_ray = tuples_sub(local_ray.origin, (*s).center);
	a = dot_product(local_ray.direction, local_ray.direction);
	b = 2 * dot_product(local_ray.direction, sphere_to_ray);
	c = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2.0) - 4 * a * c;
	if (discriminant < 0)
	{
		intersections.count = 0;
		intersections.list = NULL;
	}
	else
	{
		intersections.count = 2;
		intersections.list = malloc(sizeof(t_intersection) * 2);
		if (intersections.list)
		{
			intersections.list[0].t = (-b - sqrt(discriminant)) / (2 * a);
			intersections.list[0].obj = s;
			intersections.list[1].t = (-b + sqrt(discriminant)) / (2 * a);
			intersections.list[1].obj = s;
		}
	}
	return (intersections);
}

/**
 * @brief
 *
 * @return
 */
t_intersection	hit(t_intersections *intersections)
{
	double			t;
	unsigned int	i;
	t_intersection	inter;

	i = 0;
	t = DBL_MAX;
	inter.t = 0.0;
	inter.obj = NULL;
	while (i < intersections->count)
	{
		if (intersections->list[i].t < 0.0)
			i++;
		else if (intersections->list[i].t < t)
		{
			inter = intersections->list[i];
			t = inter.t;
		}
		else
			i++;
	}
	return (inter);
}


