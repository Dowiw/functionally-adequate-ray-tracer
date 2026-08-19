/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_fast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:28 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 17:05:34 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "util/intersections.h"

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

static inline double	inline_dot_product(t_tuple a, t_tuple b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w);
}

void	intersect_sphere_fast(t_sphere *sphere, t_ray ray, t_intersection *hit)
{
	t_ray	local_ray;
	t_tuple	sphere_to_ray;
	double	abc[3];
	double	discriminant;
	double	time;

	local_ray = inline_transform(ray, sphere->inverse);
	sphere_to_ray = (t_vector){local_ray.origin.x, local_ray.origin.y, local_ray.origin.z, VECTOR};
	abc[0] = inline_dot_product(local_ray.direction, local_ray.direction);
	abc[1] = 2 * inline_dot_product(local_ray.direction, sphere_to_ray);
	abc[2] = inline_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return ;
	time = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersection){time, (t_object){SPHERE, sphere}};
	time = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersection){time, (t_object){SPHERE, sphere}};
}
