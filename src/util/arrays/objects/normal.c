/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:32:03 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/12 15:55:15 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include <math.h>

static t_matrix4x4	get_transform(t_object *obj)
{
	if (obj->type == SPHERE)
		return (((t_sphere *)obj->object)->transform);
	else if (obj->type == PLANE)
		return (((t_plane *)obj->object)->transform);
	else if (obj->type == CYLINDER)
		return (((t_cylinder *)obj->object)->transform);
	else if (obj->type == CONE)
		return (((t_cone *)obj->object)->transform);
	return (matrix4x4_identity());
}

static t_vector	local_normal_at(t_object *obj, t_point local_point)
{
	double		dist;
	t_cylinder	*cyl;
	t_cone		*cone;
	double		y_val;

	if (obj->type == SPHERE)
		return (tuples_sub(local_point, point(0.0, 0.0, 0.0)));
	else if (obj->type == PLANE)
		return (vector(0.0, 1.0, 0.0));
	else if (obj->type == CYLINDER)
	{
		cyl = (t_cylinder *)obj->object;
		dist = pow(local_point.x, 2) + pow(local_point.z, 2);
		if (dist < 1 && local_point.y >= cyl->max - UNIT_EPSILON)
			return (vector(0.0, 1.0, 0.0));
		else if (dist < 1 && local_point.y <= cyl->min + UNIT_EPSILON)
			return (vector(0.0, -1.0, 0.0));
		return (vector(local_point.x, 0.0, local_point.z));
	}
	else if (obj->type == CONE)
	{
		cone = (t_cone *)obj->object;
		dist = pow(local_point.x, 2) + pow(local_point.z, 2);
		if (dist < pow(cone->max, 2) && local_point.y >= cone->max - UNIT_EPSILON)
			return (vector(0.0, 1.0, 0.0));
		else if (dist < pow(cone->min, 2) && local_point.y <= cone->min + UNIT_EPSILON)
			return (vector(0.0, -1.0, 0.0));
		y_val = sqrt(dist);
		if (local_point.y > 0)
			y_val = -y_val;
		return (vector(local_point.x, y_val, local_point.z));
	}
	return (vector(0.0, 0.0, 0.0));
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
	inv = matrix4x4_inverse(get_transform(obj));
	local_point = matrix4x4_multiply_tuple(inv, p);
	local_normal = local_normal_at(obj, local_point);
	world_normal = matrix4x4_multiply_tuple(matrix4x4_transpose(inv),
			local_normal);
	world_normal.w = VECTOR;
	if (calc_mag(world_normal) < UNIT_EPSILON)
		return (vector(0.0, 0.0, 0.0));
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
