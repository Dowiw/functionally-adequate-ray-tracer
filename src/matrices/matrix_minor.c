/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_minor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:36:13 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*
 * Returns the determinant of the 2x2 submatrix created by removing the
 * given 'row' and 'column' from the given 'matrix'.
 * See m3x3_submatrix and m2x2_determinant.
 */
double	m3x3_minor(t_m3x3 matrix, int row, int column)
{
	return (m2x2_determinant(m3x3_submatrix(matrix, row, column)));
}

/*
 * Returns the determinant of the 3x3 submatrix created by removing the
 * given 'row' and 'column' from the given 'matrix'.
 * See m4x4_submatrix and m3x3_determinant.
 */
double	m4x4_minor(t_m4x4 matrix, int row, int column)
{
	return (m3x3_determinant(m4x4_submatrix(matrix, row, column)));
}
