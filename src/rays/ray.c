/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/15 13:39:49 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/10 17:06:23 by kmonjard         ###   ########.fr       */
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
	r.direction = direction;
	return (r);
}
