/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:35:42 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 19:53:39 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Returns the determinant of the given 'matrix'.
 */
double	matrix2x2_determinant(t_matrix2x2 matrix)
{
	return (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]);
}

/*
 * Returns the determinant of the given 'matrix'.
 */
double	matrix3x3_determinant(t_matrix3x3 matrix)
{
	return (matrix.m[0][0] * matrix3x3_cofactor(matrix, 0, 0)
		+ matrix.m[0][1] * matrix3x3_cofactor(matrix, 0, 1)
		+ matrix.m[0][2] * matrix3x3_cofactor(matrix, 0, 2));
}

/*
 * Returns the determinant of the given 'matrix'.
 */
double	matrix4x4_determinant(t_matrix4x4 matrix)
{
	return (matrix.m[0][0] * matrix4x4_cofactor(matrix, 0, 0)
		+ matrix.m[0][1] * matrix4x4_cofactor(matrix, 0, 1)
		+ matrix.m[0][2] * matrix4x4_cofactor(matrix, 0, 2)
		+ matrix.m[0][3] * matrix4x4_cofactor(matrix, 0, 3));
}
