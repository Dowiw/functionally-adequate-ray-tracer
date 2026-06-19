/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:38:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:32:44 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

/**
 * @brief Returns a rotation matrix that rotates a point or vector around the 'x' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the X axis
 */
t_matrix4x4	matrix4x4_rotation_x(double radians)
{
	return ((t_matrix4x4){{
		{1.0, 0.0, 0.0, 0.0},
		{0.0, cos(radians), -sin(radians), 0.0},
		{0.0, sin(radians), cos(radians), 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}

/**
 * @brief Returns a rotation matrix that rotates a point or vector around the 'y' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the Y axis
 */
t_matrix4x4	matrix4x4_rotation_y(double radians)
{
	return ((t_matrix4x4){{
		{cos(radians), 0.0, sin(radians), 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{-sin(radians), 0.0, cos(radians), 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}

/**
 * @brief Returns a rotation matrix that rotates a point or vector around the 'z' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the Z axis
 */
t_matrix4x4	matrix4x4_rotation_z(double radians)
{
	return ((t_matrix4x4){{
		{cos(radians), -sin(radians), 0.0, 0.0},
		{sin(radians), cos(radians), 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}
