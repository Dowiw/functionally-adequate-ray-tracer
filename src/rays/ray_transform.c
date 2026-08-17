/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:45:39 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/12 15:55:14 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

/**
 * @brief Transform ray using transformation matrix
 * 
 * @param r ray
 * @param m transformation matrix
 * @return t_ray ray
 */
t_ray	transform(t_ray r, t_matrix4x4 m)
{
	t_ray	t;

	t.origin = matrix4x4_multiply_tuple(m, r.origin);
	t.direction = matrix4x4_multiply_tuple(m, r.direction);
	return (t);
}

/**
 * @brief Set the transform of an object.
 * 
 * @param obj
 * @param t
 */
void	set_transform(t_object *obj, t_matrix4x4 t)
{
	if (!obj || !obj->object)
		return ;
	if (obj->type == SPHERE)
		((t_sphere *)obj->object)->transform = t;
	else if (obj->type == CYLINDER)
		((t_cylinder *)obj->object)->transform = t;
	else if (obj->type == PLANE)
		((t_plane *)obj->object)->transform = t;
	else if (obj->type == CONE)
		((t_cone *)obj->object)->transform = t;
}

/**
 * @brief Calculate the position of a ray based on time
 * 
 * @param ray ray struct
 * @param time time value
 * @return t_point position of ray after time
 */
t_point	position(t_ray ray, double time)
{
	return (tuples_add(ray.origin, tuple_mult(ray.direction, time)));
}
