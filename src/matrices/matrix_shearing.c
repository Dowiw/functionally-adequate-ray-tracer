/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_shearing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:00:38 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:39:17 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a shearing matrix that changes a point or vector in each dimension relative to its other components.
 *
 * @param xy - How much X changes in proportion to Y
 * @param xz - How much X changes in proportion to Z
 * @param yx - How much Y changes in proportion to X
 * @param yz - How much Y changes in proportion to Z
 * @param zx - How much Z changes in proportion to X
 * @param zy - How much Z changes in proportion to Y
 * @return Shearing Matrix
 */
t_matrix4x4	matrix4x4_shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
	return ((t_matrix4x4){{
		{1.0, xy, xz, 0.0},
		{yx, 1.0, yz, 0.0},
		{zx, zy, 1.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}
