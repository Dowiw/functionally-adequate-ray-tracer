/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:58:53 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# ifndef VECTOR
#  define VECTOR 0.0
# endif
# ifndef POINT
#  define POINT 1.0
# endif
# ifndef INVALID_NEG
#  define INVALID_NEG -1.0
# endif
# ifndef INVALID_POS
#  define INVALID_POS 2.0
# endif
# ifndef COLOR
#  define COLOR 3.0
# endif

# ifndef PI
#  define PI 3.14159265358979323846
# endif

# ifndef PIXELS_PER_FRAME
#  define PIXELS_PER_FRAME 1000
# endif

int			compare_doubles(const double a, const double b);
int			compare_tuples(const t_tuple *a, const t_tuple *b);

t_point		point(double x, double y, double z);
t_vector	vector(double x, double y, double z);
t_color		color(double x, double y, double z);

double		calc_mag(const t_tuple a);
double		dot_product(const t_tuple a, const t_tuple b);
t_tuple		calc_norm(const t_tuple a);
t_tuple		cross_product(const t_tuple a, const t_tuple b);

t_tuple		tuples_add(const t_tuple a, const t_tuple b);
t_tuple		tuples_sub(const t_tuple a, const t_tuple b);
t_tuple		tuple_neg(const t_tuple a);
t_tuple		tuple_mult(const t_tuple a, const double scalar);
t_tuple		tuple_div(const t_tuple a, const double scalar);

t_tuple		shur_prod(const t_tuple color_a, const t_tuple color_b);
int			clamp_color(double color);
t_color		color_black(void);

t_m2x2		m2x2_identity(void);
t_m3x3		m3x3_identity(void);
t_m4x4		m4x4_identity(void);

int			m2x2_compare(t_m2x2 a, t_m2x2 b);
int			m3x3_compare(t_m3x3 a, t_m3x3 b);
int			m4x4_compare(t_m4x4 a, t_m4x4 b);

t_m2x2		m2x2_multiply(t_m2x2 a, t_m2x2 b);
t_m3x3		m3x3_multiply(t_m3x3 a, t_m3x3 b);
t_m4x4		m4x4_multiply(t_m4x4 a, t_m4x4 b);

t_tuple		m4x4_multiply_tuple(t_m4x4 a, t_tuple b);

t_m2x2		m2x2_transpose(t_m2x2 matrix);
t_m3x3		m3x3_transpose(t_m3x3 matrix);
t_m4x4		m4x4_transpose(t_m4x4 matrix);

double		m2x2_determinant(t_m2x2 matrix);
double		m3x3_determinant(t_m3x3 matrix);
double		m4x4_determinant(t_m4x4 matrix);

t_m2x2		m3x3_submatrix(t_m3x3 matrix, int row, int column);
t_m3x3		m4x4_submatrix(t_m4x4 matrix, int row, int column);

double		m3x3_minor(t_m3x3 matrix, int row, int column);
double		m4x4_minor(t_m4x4 matrix, int row, int column);

double		m3x3_cofactor(t_m3x3 matrix, int row, int column);
double		m4x4_cofactor(t_m4x4 matrix, int row, int column);

t_m2x2		m2x2_inverse(t_m2x2 matrix);
t_m3x3		m3x3_inverse(t_m3x3 matrix);
t_m4x4		m4x4_inverse(t_m4x4 matrix);

t_m4x4		m4x4_translation(double x, double y, double z);

t_m4x4		m4x4_scaling(double x, double y, double z);

t_m4x4		m4x4_rotation_x(double radians);
t_m4x4		m4x4_rotation_y(double radians);
t_m4x4		m4x4_rotation_z(double radians);
t_m4x4		m4x4_rotation(t_vector direction);

t_m4x4		m4x4_shearing(double *params);

t_m4x4		view_transform(t_point from, t_point to, t_vector up);

t_point		position(t_ray ray, double time);
t_ray		transform(t_ray r, t_m4x4 m);
t_ray		ray(t_point origin, t_vector direction);

t_vector	reflect(t_vector v, t_vector n);

#endif
