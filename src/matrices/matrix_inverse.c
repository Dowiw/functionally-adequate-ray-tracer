/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_inverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:36:36 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:40:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Computes the inverse of a 2x2 matrix.
 *
 * @param m the matrix to invert
 * @return the inverted 2x2 matrix
 */
t_m2x2	m2x2_inverse(t_m2x2 matrix)
{
	return (matrix);
}

/*
 * Returns the inverse of the given 'matrix'.
 * The inverse is a matrix with each element being set to the cofactor of its
 * position in the given 'matrix', divided by the determinant and then
 * transposed.
 * If the determinant of the given 'matrix' is 0, this function returns the
 * matrix without changes, however this case should be checked seperately
 * by each call site if applicable.
 */
t_m3x3	m3x3_inverse(t_m3x3 matrix)
{
	t_m3x3	result;
	double	determinant;
	int		r;
	int		c;

	determinant = m3x3_determinant(matrix);
	if (determinant == 0)
		return (matrix);
	r = 0;
	while (r < 3)
	{
		c = 0;
		while (c < 3)
		{
			result.m[c][r] = m3x3_cofactor(matrix, r, c) / determinant;
			c++;
		}
		r++;
	}
	return (result);
}

/*
 * Returns the inverse of the given 'matrix'.
 * The inverse is a matrix with each element being set to the cofactor of its
 * position in the given 'matrix', divided by the determinant and then
 * transposed.
 * If the determinant of the given 'matrix' is 0, this function returns the
 * matrix without changes, however this case should be checked seperately
 * by each call site if applicable.
 */
t_m4x4	m4x4_inverse(t_m4x4 matrix)
{
	t_m4x4	result;
	double	determinant;
	int		r;
	int		c;

	determinant = m4x4_determinant(matrix);
	if (determinant == 0)
		return (matrix);
	r = 0;
	while (r < 4)
	{
		c = 0;
		while (c < 4)
		{
			result.m[c][r] = m4x4_cofactor(matrix, r, c) / determinant;
			c++;
		}
		r++;
	}
	return (result);
}
