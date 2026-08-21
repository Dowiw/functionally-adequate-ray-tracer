/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:45:39 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 18:18:33 by sstark           ###   ########.fr       */
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
t_ray	transform(t_ray r, t_m4x4 m)
{
	t_ray	t;

	t.origin = m4x4_multiply_tuple(m, r.origin);
	t.dir = m4x4_multiply_tuple(m, r.dir);
	return (t);
}

/**
 * @brief Set the transform of an object.
 *
 * @param obj
 * @param t
 */
void	set_transform(t_object *obj, t_m4x4 t)
{
	if (!obj || !obj->ptr)
		return ;
	if (obj->type == SPHERE)
	{
		((t_sphere *)obj->ptr)->transform = t;
		((t_sphere *)obj->ptr)->inverse = m4x4_inverse(t);
	}
	else if (obj->type == CYLINDER)
	{
		((t_cylinder *)obj->ptr)->transform = t;
		((t_cylinder *)obj->ptr)->inverse = m4x4_inverse(t);
	}
	else if (obj->type == PLANE)
	{
		((t_plane *)obj->ptr)->transform = t;
		((t_plane *)obj->ptr)->inverse = m4x4_inverse(t);
	}
	else if (obj->type == CONE)
	{
		((t_cone *)obj->ptr)->transform = t;
		((t_cone *)obj->ptr)->inverse = m4x4_inverse(t);
	}
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
	return (tuples_add(ray.origin, tuple_mult(ray.dir, time)));
}
