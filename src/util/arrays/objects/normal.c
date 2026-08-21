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

/**
 * @brief Retrieves the inverse transformation matrix of a generic shape
 * object.
 *
 * @param obj pointer to the object
 * @return the inverse 4x4 matrix
 */
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

/**
 * @brief Calculates the local surface normal of a generic object at a
 * specific point.
 *
 * @param obj pointer to the object
 * @param point the local point on the surface
 * @return the local normal vector
 */
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

/**
 * @brief Calculates the local normal on a cylinder's surface or caps.
 *
 * @param cylinder pointer to the cylinder object
 * @param point the local point on the cylinder
 * @return the local normal vector
 */
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

/**
 * @brief Calculates the local normal on a cone's surface or caps.
 *
 * @param cone pointer to the cone object
 * @param point the local point on the cone
 * @return the local normal vector
 */
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
