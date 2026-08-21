/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_fast.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:23:36 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:45:18 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "util/intersections.h"

/**
 * @brief Inline double raised by 2
 * 
 * @param d 
 * @return double 
 */
static inline double	pow2(double d)
{
	return (d * d);
}

/**
 * @brief Fast check for ray intersection with the caps of a cylinder.
 * Evaluates if the ray hits the end caps within the cylinder's radius.
 *
 * @param cylinder pointer to the cylinder object
 * @param ray transformed ray targeting the cylinder
 * @param hit pointer to store the closest valid intersection
 */
static inline void	intersect_caps_fast(t_cylinder *cyl, t_ray r,
		t_intersect *hit)
{
	double	t;

	if (!cyl->closed || fabs(r.dir.y) < UNIT_EPSILON)
		return ;
	t = (cyl->min - r.origin.y) / r.dir.y;
	if (pow2(r.origin.x + t * r.dir.x) + pow2(r.origin.z + t * r.dir.z) <= 1
		&& t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CYLINDER, cyl}};
	t = (cyl->max - r.origin.y) / r.dir.y;
	if (pow2(r.origin.x + t * r.dir.x) + pow2(r.origin.z + t * r.dir.z) <= 1
		&& t >= 0.0 && (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CYLINDER, cyl}};
}

/**
 * @brief Inline optimization for matrix-tuple multiplication.
 * Avoids function call overhead for fast intersections.
 *
 * @param a the 4x4 matrix
 * @param b the tuple to multiply
 * @return the resulting transformed tuple
 */
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

/**
 * @brief Inline optimization for transforming a ray into object space.
 * Avoids function call overhead during fast intersections.
 *
 * @param r the incident ray
 * @param inv the inverse transformation matrix
 * @return the transformed ray
 */
static inline t_ray	inline_transform(t_ray r, t_m4x4 inv)
{
	return ((t_ray){inline_m4x4_multiply_tuple(inv, r.origin),
		inline_m4x4_multiply_tuple(inv, r.dir)});
}

/**
 * @brief Fast overarching intersection check for a cylinder.
 * Applies ray transformations and resolves both wall and cap intersections.
 *
 * @param cylinder pointer to the cylinder object
 * @param ray incident world-space ray
 * @param hit pointer to store the closest valid intersection
 */
void	intersect_cylinder_fast(t_cylinder *cyl, t_ray ray,
		t_intersect *hit)
{
	double	abc[3];
	double	disc;
	double	t;
	double	y;

	ray = inline_transform(ray, cyl->inverse);
	abc[0] = pow2(ray.dir.x) + pow2(ray.dir.z);
	if (abc[0] < UNIT_EPSILON)
		return (intersect_caps_fast(cyl, ray, hit));
	abc[1] = (2 * ray.origin.x * ray.dir.x) + (2 * ray.origin.z * ray.dir.z);
	abc[2] = pow2(ray.origin.x) + pow2(ray.origin.z) - 1;
	disc = pow2(abc[1]) - (4 * abc[0] * abc[2]);
	if (disc < 0)
		return ;
	t = (-abc[1] - sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (cyl->min < y && y < cyl->max && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CYLINDER, cyl}};
	t = (-abc[1] + sqrt(disc)) / (2 * abc[0]);
	y = ray.origin.y + t * ray.dir.y;
	if (cyl->min < y && y < cyl->max && t >= 0.0
		&& (hit->t == -1.0 || t < hit->t))
		*hit = (t_intersect){t, (t_object){CYLINDER, cyl}};
	intersect_caps_fast(cyl, ray, hit);
}
