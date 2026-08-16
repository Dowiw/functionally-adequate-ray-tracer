/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:32:03 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/16 17:01:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

static t_matrix4x4	get_inverse_transform(t_object *obj)
{
	if (obj->type == SPHERE)
		return (((t_sphere *)obj->object)->inverse);
	else if (obj->type == PLANE)
		return (((t_plane *)obj->object)->inverse);
	else if (obj->type == CYLINDER)
		return (((t_cylinder *)obj->object)->inverse);
	return (matrix4x4_identity());
}

static t_vector	local_normal_at(t_object *obj, t_point local_point)
{
	if (obj->type == SPHERE)
		return ((t_tuple){local_point.x, local_point.y, local_point.z, VECTOR});
	else if (obj->type == PLANE)
		return ((t_tuple){0.0, 1.0, 0.0, VECTOR});
	return ((t_tuple){0.0, 0.0, 0.0, VECTOR});
}

/**
 * @brief Return the normalized vector of an object at p
 *
 * @param obj object
 * @param p world_point
 * @return t_vector normalized vector
 */
t_vector	normal_at(t_object *obj, t_point p)
{
	t_point		local_point;
	t_vector	local_normal;
	t_vector	world_normal;
	t_matrix4x4	inv;

	if (!obj || !obj->object)
		return (vector(0.0, 0.0, 0.0));
	inv = get_inverse_transform(obj);
	local_point = matrix4x4_multiply_tuple(inv, p);
	local_normal = local_normal_at(obj, local_point);
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
