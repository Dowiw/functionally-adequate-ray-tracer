/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_cofactor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:36:26 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 20:04:16 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Returns the cofactor of the given 'matrix' at position 'row' and 'column'.
 * The cofactor is calculated by getting the minor (see matrix3x3_minor),
 * then inverting its sign if 'row' + 'column' is an odd number.
 */
double	matrix3x3_cofactor(t_matrix3x3 matrix, int row, int column)
{
	if ((row + column) & 1)
		return (-matrix3x3_minor(matrix, row, column));
	return (matrix3x3_minor(matrix, row, column));
}

/*
 * Returns the cofactor of the given 'matrix' at position 'row' and 'column'.
 * The cofactor is calculated by getting the minor (see matrix4x4_minor),
 * then inverting its sign if 'row' + 'column' is an odd number.
 */
double	matrix4x4_cofactor(t_matrix4x4 matrix, int row, int column)
{
	if ((row + column) & 1)
		return (-matrix4x4_minor(matrix, row, column));
	return (matrix4x4_minor(matrix, row, column));
}
