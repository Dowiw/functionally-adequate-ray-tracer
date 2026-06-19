/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 12:38:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:00:02 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"

t_matrix4x4	matrix4x4_rotation_x(double radians)
{
	return ((t_matrix4x4){{
		{1.0, 0.0, 0.0, 0.0},
		{0.0, cos(radians), -sin(radians), 0.0},
		{0.0, sin(radians), cos(radians), 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}

t_matrix4x4	matrix4x4_rotation_y(double radians)
{
	return ((t_matrix4x4){{
		{cos(radians), 0.0, sin(radians), 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{-sin(radians), 0.0, cos(radians), 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}

t_matrix4x4	matrix4x4_rotation_z(double radians)
{
	return ((t_matrix4x4){{
		{cos(radians), -sin(radians), 0.0, 0.0},
		{sin(radians), cos(radians), 0.0, 0.0},
		{0.0, 0.0, 0.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}
