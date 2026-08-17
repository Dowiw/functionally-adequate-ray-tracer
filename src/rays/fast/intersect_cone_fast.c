/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone_fast.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 18:53:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/17 19:29:46 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "ray.h"
#include "scene.h"
#include "util/intersections.h"

// TODO
void	intersect_cone_fast(t_cone *cone, t_ray ray, t_intersection *hit)
{
	t_intersections	xs;
	int				i;
	double			time;

	xs = intersect_cone(cone, ray);
	i = 0;
	while (i < xs.count)
	{
		time = xs.list[i]->t;
		if (time >= 0.0 && (hit->t == -1.0 || time < hit->t))
			*hit = *xs.list[i];
		i++;
	}
	free_intersections(xs);
}
