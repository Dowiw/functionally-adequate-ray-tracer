/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_fast.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:23:36 by sstark            #+#    #+#             */
/*   Updated: 2026/08/18 14:25:05 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"

static inline double	pow2(double d)
{
	return (d * d);
}
static inline int		check_cap_fast(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (pow2(x) + pow2(z) <= 1);
}

static inline void		intersect_caps_fast(t_cylinder *cyl, t_ray r, t_intersection *hit)
{
	double	t;

	if (!cyl->closed || fabs(r.direction.y) < UNIT_EPSILON)
		return ;
	t = (cyl->min - r.origin.y) / r.direction.y;
	if (check_cap_fast(r, t) && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CYLINDER, cyl}};
	t = (cyl->max - r.origin.y) / r.direction.y;
	if (check_cap_fast(r, t) && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CYLINDER, cyl}};
}

static inline t_tuple	inline_matrix4x4_multiply_tuple(t_matrix4x4 a, t_tuple b)
{
	t_tuple	result;

	result.x = a.m[0][0] * b.x
		+ a.m[0][1] * b.y
		+ a.m[0][2] * b.z
		+ a.m[0][3] * b.w;
	result.y = a.m[1][0] * b.x
		+ a.m[1][1] * b.y
		+ a.m[1][2] * b.z
		+ a.m[1][3] * b.w;
	result.z = a.m[2][0] * b.x
		+ a.m[2][1] * b.y
		+ a.m[2][2] * b.z
		+ a.m[2][3] * b.w;
	result.w = a.m[3][0] * b.x
		+ a.m[3][1] * b.y
		+ a.m[3][2] * b.z
		+ a.m[3][3] * b.w;
	return (result);
};

static inline t_ray		inline_transform(t_ray r, t_matrix4x4 m)
{
	return ((t_ray){inline_matrix4x4_multiply_tuple(m, r.origin), inline_matrix4x4_multiply_tuple(m, r.direction)});
}

void	intersect_cylinder_fast(t_cylinder *cylinder, t_ray ray, t_intersection *hit)
{
	double		abc[3];
	double		disc;
	double		t;
	double		y;

	ray = inline_transform(ray, cylinder->transform);
	abc[0] = pow2(ray.direction.x) + pow2(ray.direction.z);
	if (abc[0] < UNIT_EPSILON)
	{
		intersect_caps_fast(cylinder, ray, hit);
		return ;
	}
	abc[1] = (2 * ray.origin.x * ray.direction.x) + (2 * ray.origin.z * ray.direction.z);
	abc[2] = pow2(ray.origin.x) + pow2(ray.origin.z) - 1;
	disc = pow2(abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return ;
	t = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.direction.y;
	if (cylinder->min < y && y < cylinder->max && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CYLINDER, cylinder}};
	t = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.direction.y;
	if (cylinder->min < y && y < cylinder->max && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CYLINDER, cylinder}};
	intersect_caps_fast(cylinder, ray, hit);
}
