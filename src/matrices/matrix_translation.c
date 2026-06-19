/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 11:24:23 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:35:53 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a translation matrix that translates (offsets) a point by 'x', 'y' and 'z'.
 * NOTE: Vectors are not affected by this matrix.
 *
 * @param x
 * @param y
 * @param z
 * @return t_matrix4x4
 */
t_matrix4x4	matrix4x4_translation(double x, double y, double z)
{
	return ((t_matrix4x4){{
		{1.0, 0.0, 0.0, x},
		{0.0, 1.0, 0.0, y},
		{0.0, 0.0, 1.0, z},
		{0.0, 0.0, 0.0, 1.0}
	}});
}
