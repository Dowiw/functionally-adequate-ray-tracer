/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_fast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:53:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:07:21 by sstark           ###   ########.fr       */
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

static inline int		check_cap_fast(t_ray r, double t, double y)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (pow2(x) + pow2(z) <= pow2(y));
}

static inline void		intersect_caps_fast(t_cone *cone, t_ray r, t_intersection *hit)
{
	double	t;

	if (!cone->closed || fabs(r.direction.y) < UNIT_EPSILON)
		return ;
	t = (cone->min - r.origin.y) / r.direction.y;
	if (check_cap_fast(r, t, cone->min) && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CONE, cone}};
	t = (cone->max - r.origin.y) / r.direction.y;
	if (check_cap_fast(r, t, cone->max) && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CONE, cone}};
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

void	intersect_cone_fast(t_cone *cone, t_ray ray, t_intersection *hit)
{
	double			abc[3];
	double			disc;
	double			t;
	double			y;

	ray = inline_transform(ray, cone->inverse);
	abc[0] = pow2(ray.direction.x) - pow2(ray.direction.y)
		+ pow2(ray.direction.z);
	abc[1] = (2 * ray.origin.x * ray.direction.x)
		- (2 * ray.origin.y * ray.direction.y)
		+ (2 * ray.origin.z * ray.direction.z);
	abc[2] = pow2(ray.origin.x) - pow2(ray.origin.y)
		+ pow2(ray.origin.z);
	if (fabs(abc[0]) < UNIT_EPSILON)
	{
		if (fabs(abc[1]) < UNIT_EPSILON)
		{
			intersect_caps_fast(cone, ray, hit);
			return ;
		}
		t = -abc[2] / abc[1];
		y = ray.origin.y + t * ray.direction.y;
		if (cone->min < y && y < cone->max && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
			*hit = (t_intersection){t, (t_object){CONE, cone}};
		intersect_caps_fast(cone, ray, hit);
		return ;
	}
	disc = pow2(abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
	{
		intersect_caps_fast(cone, ray, hit);
		return ;
	}
	t = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.direction.y;
	if (cone->min < y && y < cone->max && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CONE, cone}};
	t = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.direction.y;
	if (cone->min < y && y < cone->max && t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersection){t, (t_object){CONE, cone}};
	intersect_caps_fast(cone, ray, hit);
}
