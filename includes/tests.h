#ifndef TESTS_H
# define TESTS_H

int	test_t_tuple_values(void);
int	test_tuple_utils(void);
int	test_tuple_addition(void);
int	test_tuple_subtraction(void);
int	test_tuple_negate(void);
int	test_tuple_mul(void);
int	test_tuple_div(void);
int	test_tuple_mag(void);
int	test_tuple_norm(void);
int	test_tuple_dot(void);
int	test_tuple_cross(void);

int	test_color(void);
int	test_color_add(void);
int	test_color_sub(void);
int	test_color_mult_scalar(void);
int	test_color_mult(void);

int	test_canvas(void);
int	test_canvas_place(void);
int	test_canvas_ppm(void);

int	test_matrix_values(void);
int	test_matrix_identity(void);
int	test_matrix_compare(void);
int	test_matrix_multiply(void);
int	test_matrix_multiply_tuple(void);
int	test_matrix_transpose(void);
int	test_matrix_determinant(void);
int	test_matrix_submatrix(void);
int	test_matrix_minor(void);
int	test_matrix_cofactor(void);
int	test_matrix_inverse(void);

int	test_translation(void);
int	test_scaling(void);
int	test_rotation(void);
int	test_shearing(void);
int	test_chaining(void);

#endif
