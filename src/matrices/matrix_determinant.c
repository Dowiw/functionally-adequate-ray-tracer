/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:35:42 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Returns the determinant of the given 'matrix'.
 */
double	m2x2_determinant(t_m2x2 matrix)
{
	return (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
}

/*
 * Returns the determinant of the given 'matrix'.
 */
double	m3x3_determinant(t_m3x3 matrix)
{
	return (matrix.m[0][0] * m3x3_cofactor(matrix, 0, 0)
		+ matrix.m[0][1] * m3x3_cofactor(matrix, 0, 1)
		+ matrix.m[0][2] * m3x3_cofactor(matrix, 0, 2));
}

/*
 * Returns the determinant of the given 'matrix'.
 */
double	m4x4_determinant(t_m4x4 matrix)
{
	return (matrix.m[0][0] * m4x4_cofactor(matrix, 0, 0)
		+ matrix.m[0][1] * m4x4_cofactor(matrix, 0, 1)
		+ matrix.m[0][2] * m4x4_cofactor(matrix, 0, 2)
		+ matrix.m[0][3] * m4x4_cofactor(matrix, 0, 3));
}
