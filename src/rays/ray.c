/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:39:49 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 18:16:11 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Ray constructor
 *
 * @param origin
 * @param direction
 * @return the resulting struct
 */
t_ray	ray(t_point origin, t_vector direction)
{
	t_ray	r;

	r.origin = origin;
	r.dir = direction;
	return (r);
}
