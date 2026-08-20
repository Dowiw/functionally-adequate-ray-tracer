/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:33:53 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		matrix_multiply(double *result, double *a, double *b, int size);
static double	matrix_product(double *a, double *b, int *rc, int size);

/*
 * Multiplies the given matrices 'a' and 'b'.
 * The product for each element in the resulting matrix is calculated by
 * multiplying elements in its row in matrix 'a' with elements in its
 * column in matrix 'b' in sequence.
 * For example the product of [1, 0] would be calculated like this:
 *  a[1][0] * b[0][0] + a[1][1] * b[1][0]
 */
t_m2x2	m2x2_multiply(t_m2x2 a, t_m2x2 b)
{
	t_m2x2	result;

	matrix_multiply(&result.m[0][0], &a.m[0][0], &b.m[0][0], 2);
	return (result);
}

/*
 * Multiplies the given matrices 'a' and 'b'.
 * The product for each element in the resulting matrix is calculated by
 * multiplying elements in its row in matrix 'a' with elements in its
 * column in matrix 'b' in sequence.
 * For example the product of [1, 2] would be calculated like this:
 *  a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2]
 */
t_m3x3	m3x3_multiply(t_m3x3 a, t_m3x3 b)
{
	t_m3x3	result;

	matrix_multiply(&result.m[0][0], &a.m[0][0], &b.m[0][0], 3);
	return (result);
}

/*
 * Multiplies the given matrices 'a' and 'b'.
 * The product for each element in the resulting matrix is calculated by
 * multiplying elements in its row in matrix 'a' with elements in its
 * column in matrix 'b' in sequence.
 * For example the product of [1, 2] would be calculated like this:
 * a[1][0] * b[0][2] + a[1][1] * b[1][2] + a[1][2] * b[2][2] + a[1][3] *
 * b[3][2]
 */
t_m4x4	m4x4_multiply(t_m4x4 a, t_m4x4 b)
{
	t_m4x4	result;

	matrix_multiply(&result.m[0][0], &a.m[0][0], &b.m[0][0], 4);
	return (result);
}

/**
 * @brief Multiplies two matrices of arbitrary size.
 *
 * @param res pointer to the resulting matrix (flat array)
 * @param a pointer to the first matrix (flat array)
 * @param b pointer to the second matrix (flat array)
 * @param size the dimension of the matrices (e.g., 4 for 4x4)
 */
static void	matrix_multiply(double *result, double *a, double *b, int size)
{
	int	r;
	int	c;
	int	rc[2];

	r = 0;
	while (r < size)
	{
		c = 0;
		while (c < size)
		{
			rc[0] = r;
			rc[1] = c;
			result[r * size + c] = matrix_product(a, b, rc, size);
			c++;
		}
		r++;
	}
}

/**
 * @brief Computes the dot product of a specific row and column for matrix
 * multiplication.
 *
 * @param a pointer to the first matrix
 * @param b pointer to the second matrix
 * @param rc row col current index pair (encoded as size, row, col array)
 * @param size ^^^
 * @return the scalar product for that matrix cell
 */
static double	matrix_product(double *a, double *b, int *rc, int size)
{
	double	product;
	int		i;

	product = 0.0;
	i = 0;
	while (i < size)
	{
		product += a[rc[0] * size + i] * b[i * size + rc[1]];
		i++;
	}
	return (product);
}
