/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_transpose.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:34:42 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Transposes an arbitrary size matrix (swaps rows and columns).
 *
 * @param res pointer to the resulting transposed matrix
 * @param m pointer to the source matrix
 * @param size the dimension of the matrix
 */
static void	matrix_transpose(double *result, double *matrix, int rows,
				int columns);

/*
 * Returns the transposed version of the given 'matrix'.
 * A matrix is transposed by flipping its rows and columns
 * Each element matrix[0][1] gets put into result[1][0] and so forth.
 */
t_m2x2	m2x2_transpose(t_m2x2 matrix)
{
	t_m2x2	result;

	matrix_transpose(&result.m[0][0], &matrix.m[0][0], 2, 2);
	return (result);
}

/*
 * Returns the transposed version of the given 'matrix'.
 * A matrix is transposed by flipping its rows and columns
 * Each element matrix[0][1] gets put into result[1][0] and so forth.
 */
t_m3x3	m3x3_transpose(t_m3x3 matrix)
{
	t_m3x3	result;

	matrix_transpose(&result.m[0][0], &matrix.m[0][0], 3, 3);
	return (result);
}

/*
 * Returns the transposed version of the given 'matrix'.
 * A matrix is transposed by flipping its rows and columns
 * Each element matrix[0][1] gets put into result[1][0] and so forth.
 */
t_m4x4	m4x4_transpose(t_m4x4 matrix)
{
	t_m4x4	result;

	matrix_transpose(&result.m[0][0], &matrix.m[0][0], 4, 4);
	return (result);
}

/**
 * @brief Transposes an arbitrary size matrix (swaps rows and columns).
 *
 * @param res pointer to the resulting transposed matrix
 * @param m pointer to the source matrix
 * @param size the dimension of the matrix
 */
static void	matrix_transpose(double *result, double *matrix, int rows,
				int columns)
{
	int	r;
	int	c;

	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < columns)
		{
			result[c * columns + r] = matrix[r * columns + c];
			c++;
		}
		r++;
	}
}
