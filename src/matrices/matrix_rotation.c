/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:38:05 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:59:53 by sstark           ###   ########.fr       */
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
t_m4x4	m4x4_rotation_x(double radians)
{
	t_m4x4	m;

	m = m4x4_identity();
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
t_m4x4	m4x4_rotation_y(double radians)
{
	t_m4x4	m;

	m = m4x4_identity();
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
t_m4x4	m4x4_rotation_z(double radians)
{
	t_m4x4	m;

	m = m4x4_identity();
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
 * @return t_m4x4
 */
t_m4x4	m4x4_rotation(t_vector vec)
{
	double	h;
	double	v;

	if (calc_mag(vec) == 0.0)
		return (m4x4_identity());
	vec = calc_norm(vec);
	if (vec.z == 0.0)
	{
		if (vec.x > 0.0)
			h = PI * 0.5;
		else
			h = PI * 1.5;
	}
	else if (vec.z > 0.0)
		h = PI * 0.0 + atan(vec.x / vec.z);
	else
		h = PI * 1.0 + atan(vec.x / vec.z);
	if (vec.y == 0.0)
		v = PI * 0.5;
	else if (vec.y > 0.0)
		v = PI * 0.0 + atan(sqrt(vec.x * vec.x + vec.z * vec.z) / vec.y);
	else
		v = PI * 1.0 + atan(sqrt(vec.x * vec.x + vec.z * vec.z) / vec.y);
	return (m4x4_multiply(m4x4_rotation_y(h), m4x4_rotation_x(v)));
}
