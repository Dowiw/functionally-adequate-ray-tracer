/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:44:27 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/17 10:51:45 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	test_ray(void);
int	test_ray_pos(void);
int	test_ray_intersect(void);
int	test_aggregating_intersections(void);
int	test_hit(void);
int	test_ray_transform(void);
int	test_sphere_ray_transform(void);

int	test_sphere_normals(void);
int	test_sphere_normal_transform(void);
int	test_vector_reflection(void);
int	test_light_struct(void);
int	test_sphere_material(void);
int	test_sphere_lighting(void);

int	test_prepare_computations(void);
int	test_shade_hit(void);
int	test_default_scene(void);
int	test_intersect_scene(void);
int	test_color_at(void);
int	test_view_transform(void);
int	test_camera(void);
int	test_ray_for_pixel(void);
int	test_render_scene(void);

int	test_shadow_surface(void);
int	test_shadow_is_shadowed(void);
int	test_shadow_shade(void);
int	test_shadow_point_offsets(void);

int	test_planes_default(void);
int	test_planes_updated_normal(void);
int	test_planes_constant_size(void);
int	test_planes_intersections(void);
int	test_planes_no_intersections(void);

int	test_cylinders_no_intersections(void);
int	test_cylinders_intersections(void);
int	test_cylinders_normal(void);
int	test_cylinders_min_max(void);
int	test_cylinders_truncated(void);
int	test_cylinders_closed(void);
int	test_cylinders_cap_normals(void);

int	test_cones_intersections(void);
int	test_cones_parallel_intersection(void);
int	test_cones_end_caps(void);
int	test_cones_normal(void);

#endif
