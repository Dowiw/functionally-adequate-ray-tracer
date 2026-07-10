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
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#ifndef DBL_MAX
# define DBL_MAX 1.7976931348623157e+308
#endif

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

 * @return t_intersections the collection containing the
 * aggregated intersections
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
 * @brief Assign the variables of the intersection struct.
 * This is where interects in time is assigned for a sphere.
 *
 * @param xs the struct
 * @param abc the a, b, c variables for the dot dot_product
 * @param dis
 * @param s sphere struct
 *
 * @return returns NULL if malloc fail
 */
static void	set_roots(t_intersections *xs, double *abc, double dis,
		struct s_sphere *s)
{
	xs->count = 2;
	xs->list = malloc(sizeof(t_intersection) * 2);
	if (!xs->list)
	{
		xs->count = 0;
		return ;
	}
	xs->list[0].t = (-abc[1] - sqrt(dis)) / (2 * abc[0]);
	xs->list[0].obj = s;
	xs->list[1].t = (-abc[1] + sqrt(dis)) / (2 * abc[0]);
	xs->list[1].obj = s;
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
	t_intersections	xs;
	t_tuple			s_to_r;
	double			abc[2];
	double			dis;
	t_ray			local_ray;

	local_ray = transform(r, matrix4x4_inverse(s->transform));
	s_to_r = tuples_sub(local_ray.origin, s->center);
	abc[0] = dot_product(local_ray.direction, local_ray.direction);
	abc[1] = 2 * dot_product(local_ray.direction, s_to_r);
	dis = abc[1] * abc[1] - 4 * abc[0] * (dot_product(s_to_r, s_to_r) - 1);
	if (dis < 0)
	{
		xs.count = 0;
		xs.list = NULL;
	}
	else
		set_roots(&xs, abc, dis, s);
	return (xs);
}

/**
 * @brief Find the lowest possible positive value and assign it as the hit
 * for a sphere.
 *
 * @return the intersection that has that hit
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
