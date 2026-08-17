/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:30:00 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/17 13:30:00 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"
#include <math.h>

/**
 * @brief Helper function to check if an intersection point on plane y lies within radius |y|
 * 
 * @param r ray
 * @param t time
 * @param y y coordinate of plane extent
 * @return int 1 if inside cap radius, 0 otherwise
 */
static int	check_cap_cone(t_ray r, double t, double y)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if (pow(x, 2.0) + pow(z, 2.0) <= pow(y, 2.0))
		return (1);
	return (0);
}

/**
 * @brief Checks for intersections on the cone end caps
 * 
 * @param cone pointer to t_cone
 * @param r ray
 * @param xs pointer to t_intersections
 */
void	intersect_caps_cone(t_cone *cone, t_ray r, t_intersections *xs)
{
	double	t;

	if (!cone->closed || fabs(r.direction.y) < UNIT_EPSILON)
		return ;
	t = (cone->min - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cone->min))
		*xs = intersections_add(*xs, create_intersection(CONE, cone, t));
	t = (cone->max - r.origin.y) / r.direction.y;
	if (check_cap_cone(r, t, cone->max))
		*xs = intersections_add(*xs, create_intersection(CONE, cone, t));
}
