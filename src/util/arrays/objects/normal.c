/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:32:03 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/20 20:58:27 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

static t_m4x4	get_inverse_transform(t_object *obj);

static t_vector	local_normal_at(t_object *obj, t_point local_point);

static t_vector	local_normal_cyl(t_cylinder *cyl, t_point local_point);

static t_vector	local_normal_cone(t_cone *cone, t_point local_point);

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
	t_m4x4		inv;

	if (!obj || !obj->ptr)
		return ((t_tuple){0.0, 0.0, 0.0, VECTOR});
	inv = get_inverse_transform(obj);
	local_point = m4x4_multiply_tuple(inv, p);
	local_normal = local_normal_at(obj, local_point);
	world_normal = m4x4_multiply_tuple(m4x4_transpose(inv),
			local_normal);
	world_normal.w = VECTOR;
	if (calc_mag(world_normal) < UNIT_EPSILON)
		return ((t_tuple){0.0, 0.0, 0.0, VECTOR});
	return (calc_norm(world_normal));
}

static t_m4x4	get_inverse_transform(t_object *obj)
{
	if (obj->type == SPHERE)
		return (((t_sphere *)obj->ptr)->inverse);
	else if (obj->type == PLANE)
		return (((t_plane *)obj->ptr)->inverse);
	else if (obj->type == CYLINDER)
		return (((t_cylinder *)obj->ptr)->inverse);
	else if (obj->type == CONE)
		return (((t_cone *)obj->ptr)->inverse);
	return (m4x4_identity());
}

static t_vector	local_normal_at(t_object *obj, t_point local_point)
{
	if (obj->type == SPHERE)
		return ((t_tuple){local_point.x, local_point.y, local_point.z, VECTOR});
	if (obj->type == PLANE)
		return ((t_tuple){0.0, 1.0, 0.0, VECTOR});
	if (obj->type == CYLINDER)
		return (local_normal_cyl((t_cylinder *) obj->ptr, local_point));
	if (obj->type == CONE)
		return (local_normal_cone((t_cone *) obj->ptr, local_point));
	return ((t_tuple){0.0, 0.0, 0.0, VECTOR});
}

static t_vector	local_normal_cyl(t_cylinder *cyl, t_point local_point)
{
	double		dist;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < 1 && local_point.y >= cyl->max - UNIT_EPSILON)
		return ((t_tuple){0.0, 1.0, 0.0, VECTOR});
	else if (dist < 1 && local_point.y <= cyl->min + UNIT_EPSILON)
		return ((t_tuple){0.0, -1.0, 0.0, VECTOR});
	return ((t_tuple){local_point.x, 0.0, local_point.z, VECTOR});
}

static t_vector	local_normal_cone(t_cone *cone, t_point local_point)
{
	double		dist;
	double		y;

	dist = pow(local_point.x, 2) + pow(local_point.z, 2);
	if (dist < pow(cone->max, 2) && local_point.y >= cone->max - UNIT_EPSILON)
		return ((t_tuple){0.0, 1.0, 0.0, VECTOR});
	if (dist < pow(cone->min, 2) && local_point.y <= cone->min + UNIT_EPSILON)
		return ((t_tuple){0.0, -1.0, 0.0, VECTOR});
	y = sqrt(dist);
	if (local_point.y > 0)
		y = -y;
	return ((t_tuple){local_point.x, y, local_point.z, VECTOR});
}
