/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:08:28 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/29 13:08:28 by kmonjard         ###   ########.fr       */
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
	local_normal = tuples_sub(local_point, s->center);
	world_normal = matrix4x4_multiply_tuple(matrix4x4_transpose(inv),
			local_normal);
	world_normal.w = VECTOR;
	return (calc_norm(world_normal));
}
