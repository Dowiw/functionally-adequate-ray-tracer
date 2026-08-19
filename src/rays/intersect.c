/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 14:28:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
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
 * @return t_intersects
 */
t_intersects	intersect(t_object *obj, t_ray ray)
{
	if (!obj || !obj->ptr)
		return (intersections_create());
	if (obj->type == SPHERE)
		return (intersect_sphere((t_sphere *)obj->ptr, ray));
	else if (obj->type == PLANE)
		return (intersect_plane((t_plane *)obj->ptr, ray));
	else if (obj->type == CYLINDER)
		return (intersect_cylinder((t_cylinder *)obj->ptr, ray));
	else if (obj->type == CONE)
		return (intersect_cone((t_cone *)obj->ptr, ray));
	return (intersections_create());
}
