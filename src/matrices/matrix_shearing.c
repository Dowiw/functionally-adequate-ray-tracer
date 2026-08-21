/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_shearing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:00:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Returns a shearing matrix that changes a point or vector in
 * each dimension relative to its other components.
 *
 * @param params - Array of 6 doubles containing xy, xz, yx, yz, zx, zy
 * @return Shearing Matrix
 */
t_m4x4	m4x4_shearing(double *params)
{
	t_m4x4	result;

	result = m4x4_identity();
	result.m[0][1] = params[0];
	result.m[0][2] = params[1];
	result.m[1][0] = params[2];
	result.m[1][2] = params[3];
	result.m[2][0] = params[4];
	result.m[2][1] = params[5];
	return (result);
}
