/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scaling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:24:44 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a scaling matrix that scales a point or vector by
 * 'x', 'y' and 'z'.
 *
 * @param x
 * @param y
 * @param z
 * @return Scaling Matrix
 */
t_m4x4	m4x4_scaling(double x, double y, double z)
{
	t_m4x4	result;

	result = m4x4_identity();
	result.m[0][0] = x;
	result.m[1][1] = y;
	result.m[2][2] = z;
	return (result);
}
