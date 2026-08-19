/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 11:47:32 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/16 16:22:05 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "scene.h"
#include "minirt.h"
#include "ray.h"
#include "util/intersections.h"

/**
 * @brief Calculate whether the point is shadowed based on the scene.
 *
 * It first calculates the vector and distance from point p to the light.
 * Then it casts a ray from that p to the light because we have the normal.
 * Then then it checks if there is an object as the ray goes to the light by
 * ensuring that it does not go over the distance between the point and the
 * light pos.
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
	t_intersection	hit;
	double			distance;
	int				shadowed;

	v = tuples_sub(w.light.pos, p);
	distance = calc_mag(v);
	direction = calc_norm(v);
	r = ray(p, direction);
	hit = intersect_scene_and_hit(&w, r);
	if (hit.t >= 0.0 && hit.t < distance)
		shadowed = 1;
	else
		shadowed = 0;
	return (shadowed);
}
