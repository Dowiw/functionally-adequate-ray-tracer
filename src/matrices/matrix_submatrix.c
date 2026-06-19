/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_submatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:35:07 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 10:41:37 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	matrix_submatrix(double *result, double *matrix, int row, int column, int size);

/*
 * Returns a new 2x2 submatrix of the given 'matrix' with the given 'row' and 'column' removed.
 */
t_matrix2x2	matrix3x3_submatrix(t_matrix3x3 matrix, int row, int column)
{
	t_matrix2x2	result;

	matrix_submatrix(&result.m[0][0], &matrix.m[0][0], row, column, 3);
	return (result);
}

/*
 * Returns a new 3x3 submatrix of the given 'matrix' with the given 'row' and 'column' removed.
 */
t_matrix3x3	matrix4x4_submatrix(t_matrix4x4 matrix, int row, int column)
{
	t_matrix3x3	result;

	matrix_submatrix(&result.m[0][0], &matrix.m[0][0], row, column, 4);
	return (result);
}

static void	matrix_submatrix(double *result, double *matrix, int row, int column, int size)
{
	int	r;
	int	c;
	int	r2;
	int	c2;

	r = 0;
	r2 = 0;
	while (r < size)
	{
		if (r != row)
		{
			c = 0;
			c2 = 0;
			while (c < size)
			{
				if (c != column)
				{
					result[r2 * (size - 1) + c2] = matrix[r * size + c];
					c2++;
				}
				c++;
			}
			r2++;
		}
		r++;
	}
}
