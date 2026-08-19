/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 17:33:57 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# define VECTOR 0.0
# define POINT 1.0
# define INVALID_NEG -1.0
# define INVALID_POS 2.0
# define COLOR 3.0

# define PI 3.14159265358979323846

# define PIXELS_PER_FRAME 1000


/** ######################################################################### *
 *  TUPLES                                                                  # *
 *  ######################################################################### */

// tuple_compare.c

int					compare_doubles(const double a, const double b);
int					compare_tuples(const t_tuple *a, const t_tuple *b);

// tuple_constructs.c

t_point				point(double x, double y, double z);
t_vector			vector(double x, double y, double z);
t_color				color(double x, double y, double z);

// tuple_utils.c

double				calc_mag(const t_tuple a);
double				dot_product(const t_tuple a, const t_tuple b);
t_tuple				calc_norm(const t_tuple a);
t_tuple				cross_product(const t_tuple a, const t_tuple b);

// tuple_operations.c

t_tuple				tuples_add(const t_tuple a, const t_tuple b);
t_tuple				tuples_sub(const t_tuple a, const t_tuple b);
t_tuple				tuple_neg(const t_tuple a);
t_tuple				tuple_mult(const t_tuple a, const double scalar);
t_tuple				tuple_div(const t_tuple a, const double scalar);

/** ######################################################################### *
 *  COLORS                                                                  # *
 *  ######################################################################### */

// colors_util.c

t_tuple				shur_prod(const t_tuple color_a, const t_tuple color_b);
int					clamp_color(double color);

// colors_grayscale.c

t_color				color_black(void);

/** ######################################################################### *
 *  GRAPHICS                                                                # *
 *  ######################################################################### */

/** ######################################################################### *
 *  MATRICES                                                                # *
 *  ######################################################################### */


t_matrix2x2			matrix2x2_identity(void);
t_matrix3x3			matrix3x3_identity(void);
t_matrix4x4			matrix4x4_identity(void);

int					matrix2x2_compare(t_matrix2x2 a, t_matrix2x2 b);
int					matrix3x3_compare(t_matrix3x3 a, t_matrix3x3 b);
int					matrix4x4_compare(t_matrix4x4 a, t_matrix4x4 b);

t_matrix2x2			matrix2x2_multiply(t_matrix2x2 a, t_matrix2x2 b);
t_matrix3x3			matrix3x3_multiply(t_matrix3x3 a, t_matrix3x3 b);
t_matrix4x4			matrix4x4_multiply(t_matrix4x4 a, t_matrix4x4 b);

t_tuple				matrix4x4_multiply_tuple(t_matrix4x4 a, t_tuple b);

t_matrix2x2			matrix2x2_transpose(t_matrix2x2 matrix);
t_matrix3x3			matrix3x3_transpose(t_matrix3x3 matrix);
t_matrix4x4			matrix4x4_transpose(t_matrix4x4 matrix);

double				matrix2x2_determinant(t_matrix2x2 matrix);
double				matrix3x3_determinant(t_matrix3x3 matrix);
double				matrix4x4_determinant(t_matrix4x4 matrix);

t_matrix2x2			matrix3x3_submatrix(t_matrix3x3 matrix, int row,
						int column);
t_matrix3x3			matrix4x4_submatrix(t_matrix4x4 matrix, int row,
						int column);

double				matrix3x3_minor(t_matrix3x3 matrix, int row, int column);
double				matrix4x4_minor(t_matrix4x4 matrix, int row, int column);

double				matrix3x3_cofactor(t_matrix3x3 matrix, int row, int column);
double				matrix4x4_cofactor(t_matrix4x4 matrix, int row, int column);

t_matrix2x2			matrix2x2_inverse(t_matrix2x2 matrix);
t_matrix3x3			matrix3x3_inverse(t_matrix3x3 matrix);
t_matrix4x4			matrix4x4_inverse(t_matrix4x4 matrix);

t_matrix4x4			matrix4x4_translation(double x, double y, double z);

t_matrix4x4			matrix4x4_scaling(double x, double y, double z);

t_matrix4x4			matrix4x4_rotation_x(double radians);
t_matrix4x4			matrix4x4_rotation_y(double radians);
t_matrix4x4			matrix4x4_rotation_z(double radians);
t_matrix4x4 		matrix4x4_rotation(t_vector direction);

t_matrix4x4			matrix4x4_shearing(double *params);

t_matrix4x4			view_transform(t_point from, t_point to, t_vector up);

/** ######################################################################### *
 *  RAYS                                                                    # *
 *  ######################################################################### */

t_point				position(t_ray ray, double time);
t_ray				transform(t_ray r, t_matrix4x4 m);
t_ray	ray(t_point origin, t_vector direction);

/** ######################################################################### *
 *  SPHERES                                                                 # *
 *  ######################################################################### */

t_vector			reflect(t_vector v, t_vector n);

#endif
