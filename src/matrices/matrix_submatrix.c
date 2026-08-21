/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_submatrix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:35:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:40:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	matrix_submatrix(double *res, double *mat, int *info);

/*
 * Returns a new 2x2 submatrix of the given 'matrix' with the given 'row'
 * and 'column' removed.
 */
t_m2x2	m3x3_submatrix(t_m3x3 matrix, int row, int column)
{
	t_m2x2	result;
	int		info[3];

	info[0] = row;
	info[1] = column;
	info[2] = 3;
	matrix_submatrix(&result.m[0][0], &matrix.m[0][0], info);
	return (result);
}

/*
 * Returns a new 3x3 submatrix of the given 'matrix' with the given 'row'
 * and 'column' removed.
 */
t_m3x3	m4x4_submatrix(t_m4x4 matrix, int row, int column)
{
	t_m3x3	result;
	int		info[3];

	info[0] = row;
	info[1] = column;
	info[2] = 4;
	matrix_submatrix(&result.m[0][0], &matrix.m[0][0], info);
	return (result);
}

/**
 * @brief Extracts a submatrix by removing a specific row and column.
 *
 * @param sub pointer to the resulting submatrix
 * @param m pointer to the source matrix
 * @param size the dimension of the source matrix
 * @param rm array containing the row and col to remove [row, col]
 */
static void	matrix_submatrix(double *res, double *mat, int *info)
{
	int	r;
	int	c;

	r = -1;
	while (++r < info[2])
	{
		if (r != info[0])
		{
			c = -1;
			while (++c < info[2])
			{
				if (c != info[1])
				{
					res[(r - (r > info[0])) * (info[2] - 1)
						+ (c - (c > info[1]))] = mat[r * info[2] + c];
				}
			}
		}
	}
}
