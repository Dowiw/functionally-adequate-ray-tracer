/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_fast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:53:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:45:42 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "util/intersections.h"

static inline void	intersect_caps_fast(t_cone *cone, t_ray r,
		t_intersect *hit)
{
	double	t;
	double	cap;

	if (!cone->closed || fabs(r.dir.y) < UNIT_EPSILON)
		return ;
	t = (cone->min - r.origin.y) / r.dir.y;
	cap = (r.origin.x + t * r.dir.x) * (r.origin.x + t * r.dir.x)
		+ (r.origin.z + t * r.dir.z) * (r.origin.z + t * r.dir.z);
	if (cap <= cone->min * cone->min && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CONE, cone}};
	t = (cone->max - r.origin.y) / r.dir.y;
	cap = (r.origin.x + t * r.dir.x) * (r.origin.x + t * r.dir.x)
		+ (r.origin.z + t * r.dir.z) * (r.origin.z + t * r.dir.z);
	if (cap <= cone->max * cone->max && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CONE, cone}};
}

static inline t_tuple	inline_m4x4_multiply_tuple(t_m4x4 a, t_tuple b)
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
}

static inline t_ray	inline_transform(t_ray r, t_m4x4 m)
{
	return ((t_ray){inline_m4x4_multiply_tuple(m, r.origin),
		inline_m4x4_multiply_tuple(m, r.dir)});
}

static inline void	intersect_cone_quad(t_cone *cone, t_ray ray, double abc[3],
				t_intersect *hit)
{
	double	disc;
	double	t;
	double	y;

	disc = abc[1] * abc[1] - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return (intersect_caps_fast(cone, ray, hit));
	t = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (cone->min < y && y < cone->max && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CONE, cone}};
	t = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (cone->min < y && y < cone->max && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CONE, cone}};
	intersect_caps_fast(cone, ray, hit);
}

void	intersect_cone_fast(t_cone *cone, t_ray ray, t_intersect *hit)
{
	double	abc[3];
	double	t;
	double	y;

	ray = inline_transform(ray, cone->inverse);
	abc[0] = ray.dir.x * ray.dir.x - ray.dir.y * ray.dir.y
		+ ray.dir.z * ray.dir.z;
	abc[1] = (2 * ray.origin.x * ray.dir.x) - (2 * ray.origin.y * ray.dir.y)
		+ (2 * ray.origin.z * ray.dir.z);
	abc[2] = ray.origin.x * ray.origin.x - ray.origin.y * ray.origin.y
		+ ray.origin.z * ray.origin.z;
	if (fabs(abc[0]) < UNIT_EPSILON)
	{
		if (fabs(abc[1]) < UNIT_EPSILON)
			return (intersect_caps_fast(cone, ray, hit));
		t = -abc[2] / abc[1];
		y = ray.origin.y + t * ray.dir.y;
		if (cone->min < y && y < cone->max && t >= 0.0
			&& (hit->t == -1.0 || t < hit->t))
			*hit = (t_intersect){t, (t_object){CONE, cone}};
		return (intersect_caps_fast(cone, ray, hit));
	}
	intersect_cone_quad(cone, ray, abc, hit);
}
