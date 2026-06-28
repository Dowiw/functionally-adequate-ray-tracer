/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_transform.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 23:45:39 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/28 23:47:19 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Transform ray using transformation matrix
 * 
 * @param r ray
 * @param m transformation matrix
 * @return t_ray ray
 */
t_ray	transform(t_ray r, t_matrix4x4 m)
{
	t_ray	t;

	t.origin = matrix4x4_multiply_tuple(m, r.origin);
	t.direction = matrix4x4_multiply_tuple(m, r.direction);
	return (t);
}
