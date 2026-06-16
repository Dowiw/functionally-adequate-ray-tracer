/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 20:26:30 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# define VECTOR 0.0
# define POINT 1.0
# define INVALID_NEG -1.0
# define INVALID_POS 2.0

typedef struct s_tuple {
	double	x;
	double	y;
	double	z;
	double	w;
}	t_tuple;

typedef t_tuple t_point;

typedef t_tuple t_vector;

typedef t_tuple t_color;

/** ######################################################################### *
 *  TUPLES                                                                  # *
 *  ######################################################################### */

// tuple_compare.c

int		compare_doubles(const double a, const double b);
int		compare_tuples(const t_tuple *a, const t_tuple *b);

// tuple_utils.c

double	calc_mag(const t_tuple a);
double	dot_product(const t_tuple a, const t_tuple b);
t_tuple	calc_norm(const t_tuple a);
t_tuple	cross_product(const t_tuple a, const t_tuple b);

// tuple_operations.c

t_tuple	tuples_add(const t_tuple a, const t_tuple b);
t_tuple	tuples_sub(const t_tuple a, const t_tuple b);
t_tuple	tuple_neg(const t_tuple a);
t_tuple	tuple_mult(const t_tuple a, const double scalar);
t_tuple	tuple_div(const t_tuple a, const double scalar);

typedef struct s_matrix2x2 {
	double	m[2][2];
}	t_matrix2x2;

typedef struct s_matrix3x3 {
	double	m[3][3];
}	t_matrix3x3;

typedef struct s_matrix4x4 {
	double	m[4][4];
}	t_matrix4x4;

# define MATRIX2X2_IDENTITY (t_matrix2x2){{ \
	{1.0, 0.0}, \
	{0.0, 1.0} \
}}
# define MATRIX3X3_IDENTITY (t_matrix3x3){{ \
	{1.0, 0.0, 0.0}, \
	{0.0, 1.0, 0.0}, \
	{0.0, 0.0, 1.0} \
}}
# define MATRIX4X4_IDENTITY (t_matrix4x4){{ \
	{1.0, 0.0, 0.0, 0.0}, \
	{0.0, 1.0, 0.0, 0.0}, \
	{0.0, 0.0, 1.0, 0.0}, \
	{0.0, 0.0, 0.0, 1.0} \
}}

int	matrix2x2_compare(t_matrix2x2 a, t_matrix2x2 b);
int	matrix3x3_compare(t_matrix3x3 a, t_matrix3x3 b);
int	matrix4x4_compare(t_matrix4x4 a, t_matrix4x4 b);

t_matrix2x2	matrix2x2_multiply(t_matrix2x2 a, t_matrix2x2 b);
t_matrix3x3	matrix3x3_multiply(t_matrix3x3 a, t_matrix3x3 b);
t_matrix4x4	matrix4x4_multiply(t_matrix4x4 a, t_matrix4x4 b);

t_tuple	matrix4x4_multiply_tuple(t_matrix4x4 a, t_tuple b);

t_matrix2x2	matrix2x2_transpose(t_matrix2x2 matrix);
t_matrix3x3	matrix3x3_transpose(t_matrix3x3 matrix);
t_matrix4x4	matrix4x4_transpose(t_matrix4x4 matrix);

double	matrix2x2_determinant(t_matrix2x2 matrix);
double	matrix3x3_determinant(t_matrix3x3 matrix);
double	matrix4x4_determinant(t_matrix4x4 matrix);

t_matrix2x2	matrix3x3_submatrix(t_matrix3x3 matrix, int row, int column);
t_matrix3x3	matrix4x4_submatrix(t_matrix4x4 matrix, int row, int column);

double	matrix3x3_minor(t_matrix3x3 matrix, int row, int column);
double	matrix4x4_minor(t_matrix4x4 matrix, int row, int column);

double	matrix3x3_cofactor(t_matrix3x3 matrix, int row, int column);
double	matrix4x4_cofactor(t_matrix4x4 matrix, int row, int column);

t_matrix2x2	matrix2x2_inverse(t_matrix2x2 matrix);
t_matrix3x3	matrix3x3_inverse(t_matrix3x3 matrix);
t_matrix4x4	matrix4x4_inverse(t_matrix4x4 matrix);

#endif
