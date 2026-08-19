/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_compare.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 17:00:46 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	matrix_compare(double *a, double *b, int rows, int columns);

/*
 * Returns 0 if the matrices 'a' and 'b' are equal, 1 if they are not.
 */
int	m2x2_compare(t_m2x2 a, t_m2x2 b)
{
	return (matrix_compare(&a.m[0][0], &b.m[0][0], 2, 2));
}

/*
 * Returns 0 if the matrices 'a' and 'b' are equal, 1 if they are not.
 */
int	m3x3_compare(t_m3x3 a, t_m3x3 b)
{
	return (matrix_compare(&a.m[0][0], &b.m[0][0], 3, 3));
}

/*
 * Returns 0 if the matrices 'a' and 'b' are equal, 1 if they are not.
 */
int	m4x4_compare(t_m4x4 a, t_m4x4 b)
{
	return (matrix_compare(&a.m[0][0], &b.m[0][0], 4, 4));
}

static int	matrix_compare(double *a, double *b, int rows, int columns)
{
	int	r;
	int	c;

	r = 0;
	while (r < rows)
	{
		c = 0;
		while (c < columns)
		{
			if (compare_doubles(a[r * columns + c], b[r * columns + c]) != 0)
				return (1);
			c++;
		}
		r++;
	}
	return (0);
}
