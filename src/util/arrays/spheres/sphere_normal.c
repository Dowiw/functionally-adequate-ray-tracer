/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:08:28 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/06 19:15:05 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

/**
 * @brief Return the normalized vector of a sphere at p
 *
 * @param s s
 * @param p world_point
 * @return t_vector normalized vector
 */
t_vector	normal_at(t_sphere *s, t_point p)
{
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix4x4	inv;

	inv = matrix4x4_inverse(s->transform);
	local_point = matrix4x4_multiply_tuple(inv, p);
	local_normal = tuples_sub(local_point, point(0.0, 0.0, 0.0));
	world_normal = matrix4x4_multiply_tuple(matrix4x4_transpose(inv),
			local_normal);
	world_normal.w = VECTOR;
	return (calc_norm(world_normal));
}

/**
 * @brief Reflect the vector passed based on the normal given
 *
 * @param v vector
 * @param n normal vector
 * @return t_vector reflected vector
 */
t_vector	reflect(t_vector v, t_vector n)
{
	t_vector	r;

	r = tuples_sub(v, tuple_mult(tuple_mult(n, 2), dot_product(v, n)));
	return (r);
}
