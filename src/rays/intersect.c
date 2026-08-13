/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:28:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/12 15:55:14 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "ray.h"
#include "util/intersections.h"
#include <stdlib.h>

/**
 * @brief Generic polymorphic intersect dispatcher
 * 
 * @param obj 
 * @param ray 
 * @return t_intersections 
 */
t_intersections	intersect(t_object *obj, t_ray ray)
{
	if (!obj || !obj->object)
		return (intersections_create());
	if (obj->type == SPHERE)
		return (intersect_sphere((t_sphere *)obj->object, ray));
	else if (obj->type == PLANE)
		return (intersect_plane((t_plane *)obj->object, ray));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder((t_cylinder *)obj->object, ray));
	return (intersections_create());
}
