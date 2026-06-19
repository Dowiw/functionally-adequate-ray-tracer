/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/19 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculate the position of a ray based on time
 * 
 * @param ray ray struct
 * @param time time value
 * @return t_point position of ray after time
 */
t_point	position(t_ray ray, double time)
{
	return (tuples_add(ray.origin, tuple_mult(ray.direction, time)));
}
