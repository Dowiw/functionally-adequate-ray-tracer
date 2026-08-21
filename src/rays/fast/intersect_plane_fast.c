/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_fast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:43:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "minirt.h"
#include "util/intersections.h"

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

static inline t_ray	inline_transform(t_ray r, t_m4x4 m)
{
	return ((t_ray){inline_m4x4_multiply_tuple(m, r.origin),
		inline_m4x4_multiply_tuple(m, r.dir)});
}

/**
 * @brief Fast intersection check for an infinite plane.
 *
 * @param plane pointer to the plane object
 * @param ray incident world-space ray
 * @param hit pointer to store the resulting intersection
 */
void	intersect_plane_fast(t_plane *plane, t_ray ray, t_intersect *hit)
{
	t_ray			local_r;
	double			time;

	local_r = inline_transform(ray, plane->inverse);
	if (fabs(local_r.dir.y) < UNIT_EPSILON)
		return ;
	time = -local_r.origin.y / local_r.dir.y;
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersect){time, (t_object){PLANE, plane}};
}
