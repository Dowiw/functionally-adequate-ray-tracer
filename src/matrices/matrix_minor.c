/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_minor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:36:13 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 19:48:04 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Returns the determinant of the 2x2 submatrix created by removing the given 'row' and 'column' from the given 'matrix'.
 * See matrix3x3_submatrix and matrix2x2_determinant.
 */
double	matrix3x3_minor(t_matrix3x3 matrix, int row, int column)
{
	return (matrix2x2_determinant(matrix3x3_submatrix(matrix, row, column)));
}

/*
 * Returns the determinant of the 3x3 submatrix created by removing the given 'row' and 'column' from the given 'matrix'.
 * See matrix4x4_submatrix and matrix3x3_determinant.
 */
double	matrix4x4_minor(t_matrix4x4 matrix, int row, int column)
{
	return (matrix3x3_determinant(matrix4x4_submatrix(matrix, row, column)));
}
