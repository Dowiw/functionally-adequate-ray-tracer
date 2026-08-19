/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_fast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:53:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/18 14:28:53 by sstark           ###   ########.fr       */
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

void	intersect_cone_fast(t_cone *cone, t_ray ray, t_intersection *hit)
{
	double			abc[3];
	double			disc;
	double			t;
	double			y;

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
		t = -abc[2] / * abc[1];
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
