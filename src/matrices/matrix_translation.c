/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:24:23 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a translation matrix that translates (offsets) a point
 * by 'x', 'y' and 'z'.
 * NOTE: Vectors are not affected by this matrix.
 *
 * @param x
 * @param y
 * @param z
 * @return t_m4x4
 */
t_m4x4	m4x4_translation(double x, double y, double z)
{
	t_m4x4	result;

	result = m4x4_identity();
	result.m[0][3] = x;
	result.m[1][3] = y;
	result.m[2][3] = z;
	return (result);
}
