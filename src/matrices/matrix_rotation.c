/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:38:05 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 15:49:19 by sstark           ###   ########.fr       */
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

/**
 * @brief Returns a rotation matrix relative to vector(0.0, 1.0, 0.0)
 *
 * @param direction
 * @return t_matrix4x4
 */
t_matrix4x4 matrix4x4_rotation(t_vector direction)
{
	double	horizontal;
	double	vertical;

	if (calc_mag(direction) == 0.0)
		return (matrix4x4_identity());
	direction = calc_norm(direction);
	if (direction.z == 0.0)
	{
		if (direction.x > 0.0)
			horizontal = PI * 0.5;
		else
			horizontal = PI * 1.5;
	}
	else if (direction.z > 0.0)
		horizontal = PI * 0.0 + atan(direction.x / direction.z);
	else
		horizontal = PI * 1.0 + atan(direction.x / direction.z);
	if (direction.y == 0.0)
		vertical = PI * 0.5;
	else if (direction.y > 0.0)
		vertical = PI * 0.0 + atan(sqrt(direction.x * direction.x + direction.z * direction.z) / direction.y);
	else
		vertical = PI * 1.0 + atan(sqrt(direction.x * direction.x + direction.z * direction.z) / direction.y);
	return (matrix4x4_multiply(matrix4x4_rotation_y(horizontal), matrix4x4_rotation_x(vertical)));
}
