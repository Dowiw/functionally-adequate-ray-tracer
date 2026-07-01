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
 * @brief Returns a rotation matrix that rotates a point or vector
 * around the 'x' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the X axis
 */
t_matrix4x4	matrix4x4_rotation_x(double radians)
{
	t_matrix4x4	m;

	m = matrix4x4_identity();
	m.m[1][1] = cos(radians);
	m.m[1][2] = -sin(radians);
	m.m[2][1] = sin(radians);
	m.m[2][2] = cos(radians);
	return (m);
}

/**
 * @brief Returns a rotation matrix that rotates a point or vector
 * around the 'y' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the Y axis
 */
t_matrix4x4	matrix4x4_rotation_y(double radians)
{
	t_matrix4x4	m;

	m = matrix4x4_identity();
	m.m[0][0] = cos(radians);
	m.m[0][2] = sin(radians);
	m.m[2][0] = -sin(radians);
	m.m[2][2] = cos(radians);
	return (m);
}

/**
 * @brief Returns a rotation matrix that rotates a point or vector
 * around the 'z' axis by 'radians' degrees.
 *
 * @param radians - Rotation in radians (1 * PI is a full rotation)
 * @return Rotation Matrix around the Z axis
 */
t_matrix4x4	matrix4x4_rotation_z(double radians)
{
	t_matrix4x4	m;

	m = matrix4x4_identity();
	m.m[0][0] = cos(radians);
	m.m[0][1] = -sin(radians);
	m.m[1][0] = sin(radians);
	m.m[1][1] = cos(radians);
	return (m);
}
