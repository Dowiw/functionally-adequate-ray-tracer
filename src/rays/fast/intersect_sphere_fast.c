/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere_fast.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:28 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 16:19:14 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "util/intersections.h"

void	intersect_sphere_fast(t_sphere *sphere, t_ray ray, t_intersection *hit)
{
	t_ray	local_ray;
	t_tuple	sphere_to_ray;
	double	abc[3];
	double	discriminant;
	double	time;

	local_ray = transform(ray, sphere->inverse);
	sphere_to_ray = tuples_sub(local_ray.origin, point(0.0, 0.0, 0.0));
	abc[0] = dot_product(local_ray.direction, local_ray.direction);
	abc[1] = 2 * dot_product(local_ray.direction, sphere_to_ray);
	abc[2] = dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = abc[1] * abc[1] - 4 * abc[0] * abc[2];
	if (discriminant < 0.0)
		return ;
	time = (-abc[1] - sqrt(discriminant)) / (2 * abc[0]);
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersection){time, (t_object){SPHERE, sphere}};
	time = (-abc[1] + sqrt(discriminant)) / (2 * abc[0]);
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersection){time, (t_object){SPHERE, sphere}};
}
