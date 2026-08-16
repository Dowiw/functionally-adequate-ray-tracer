/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane_fast.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/16 16:13:30 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 16:19:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "scene.h"
#include "util/intersections.h"

void	intersect_plane_fast(t_plane *plane, t_ray ray, t_intersection *hit)
{
	t_ray			local_r;
	double			time;

	local_r = transform(ray, plane->inverse);
	if (fabs(local_r.direction.y) < UNIT_EPSILON)
		return ;
	time = -local_r.origin.y / local_r.direction.y;
	if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
		*hit = (t_intersection){time, (t_object){PLANE, plane}};
}
