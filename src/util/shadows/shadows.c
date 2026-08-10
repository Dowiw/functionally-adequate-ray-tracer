/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:47:32 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/10 17:06:23 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "scene.h"
#include "minirt.h"
#include "ray.h"
#include "util/intersections.h"

/**
 * @brief Calculate whether the point is shadowed based on the scene
 * 
 * @param w scene
 * @param p point
 * @return 0 if false, 1 if true
 */
int	is_shadowed(t_scene w, t_point p)
{
	t_vector		v;
	t_vector		direction;
	t_ray			r;
	t_intersections	xs;
	t_intersection	*hit;
	double			distance;
	int				shadowed;

	v = tuples_sub(w.light.pos, p);
	distance = calc_mag(v);
	direction = calc_norm(v);
	r = ray(p, direction);
	xs = intersect_scene(&w, r);
	hit = intersect_hit(xs);
	if (hit != NULL && hit->t < distance)
		shadowed = 1;
	else
		shadowed = 0;
	free_intersections(xs);
	return (shadowed);
}
