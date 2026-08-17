/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 10:50:34 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/17 10:51:04 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"
#include <math.h>

/**
 * @brief Helper function to check the intersect
 * 
 * @param r 
 * @param t 
 * @return int 
 */
static int	check_cap(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	if (pow(x, 2) + pow(z, 2) <= 1)
		return (1);
	return (0);
}

/**
 * @brief Checks for intersections on the caps
 * 
 * @param cyl 
 * @param r 
 * @param xs 
 */
void	intersect_caps(t_cylinder *cyl, t_ray r, t_intersections *xs)
{
	double	t;

	if (!cyl->closed || fabs(r.direction.y) < UNIT_EPSILON)
		return ;
	t = (cyl->min - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		*xs = intersections_add((*xs), create_intersection(CYLINDER, cyl, t));
	t = (cyl->max - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		*xs = intersections_add((*xs), create_intersection(CYLINDER, cyl, t));
}
