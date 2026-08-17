#include "libunit.h"
#include "tests.h"

/* Optional Setup / Teardown hooks */
// should return 0 on success

// int	suite_setup(void)
// {
// 	return (0);
// }

// int	suite_teardown(void)
// {
// 	return (0);
// }

int	main(void)
{
	t_test_suite	*suites;
	t_test_suite	*tuple_suite;
	t_test_suite	*color_suite;
	t_test_suite	*canvas_suite;
	t_test_suite	*matrices_suite;
	t_test_suite	*rays_suite;
	t_test_suite	*transformations_suite;
	t_test_suite	*light_shading_suite;
	t_test_suite	*rendering_suite;
	t_test_suite	*shadow_suite;
	t_test_suite	*planes_suite;
	t_test_suite	*cylinders_suite;
	t_test_suite	*cones_suite;

	suites = NULL;
	tuple_suite = load_suite(&suites, "Tuples Suite");
	// parser_suite->setup = suite_setup;
	// parser_suite->teardown = suite_teardown;
	load_test(tuple_suite, "Main Tuple Functionality", &test_t_tuple_values);
	load_test(tuple_suite, "Tuple Utilities", &test_tuple_utils);
	load_test(tuple_suite, "Tuple Addition", &test_tuple_addition);
	load_test(tuple_suite, "Tuple Subtraction", &test_tuple_subtraction);
	load_test(tuple_suite, "Tuple Negation", &test_tuple_negate);
	load_test(tuple_suite, "Tuple Multiplication", &test_tuple_mul);
	load_test(tuple_suite, "Tuple Division", &test_tuple_div);
	load_test(tuple_suite, "Tuple Magnitude", &test_tuple_mag);
	load_test(tuple_suite, "Tuple Normalization", &test_tuple_norm);
	load_test(tuple_suite, "Tuple Dot Product", &test_tuple_dot);
	load_test(tuple_suite, "Tuple Cross Product", &test_tuple_cross);
	color_suite = load_suite(&suites, "Colors Suite");
	load_test(color_suite, "Color Initialization", &test_color);
	load_test(color_suite, "Color Addition", &test_color_add);
	load_test(color_suite, "Color Subtraction", &test_color_sub);
	load_test(color_suite, "Color Scalar Multiplication",
		&test_color_mult_scalar);
	load_test(color_suite, "Color Multiplication (Hadamard)", &test_color_mult);
	canvas_suite = load_suite(&suites, "Canvas Suite");
	load_test(canvas_suite, "Canvas Initialization", &test_canvas);
	load_test(canvas_suite, "Canvas Utilities", &test_canvas_place);
	load_test(canvas_suite, "Canvas to PPM", &test_canvas_ppm);
	matrices_suite = load_suite(&suites, "Matrices Suite");
	load_test(matrices_suite, "Main Matrix Functionality", &test_matrix_values);
	load_test(matrices_suite, "Matrix Identities", &test_matrix_identity);
	load_test(matrices_suite, "Matrix Comparison", &test_matrix_compare);
	load_test(matrices_suite, "Matrix Multiplication", &test_matrix_multiply);
	load_test(matrices_suite, "Matrix Multiplication with Tuple",
		&test_matrix_multiply_tuple);
	load_test(matrices_suite, "Matrix Transposition", &test_matrix_transpose);
	load_test(matrices_suite, "Matrix Determinant", &test_matrix_determinant);
	load_test(matrices_suite, "Matrix Submatrix", &test_matrix_submatrix);
	load_test(matrices_suite, "Matrix Minor", &test_matrix_minor);
	load_test(matrices_suite, "Matrix Cofactor", &test_matrix_cofactor);
	load_test(matrices_suite, "Matrix Inversion", &test_matrix_inverse);
	transformations_suite = load_suite(&suites, "Transformations Suite");
	load_test(transformations_suite, "Translation", &test_translation);
	load_test(transformations_suite, "Scaling", &test_scaling);
	load_test(transformations_suite, "Rotation", &test_rotation);
	load_test(transformations_suite, "Shearing", &test_shearing);
	load_test(transformations_suite, "Chained Transformations", &test_chaining);
	rays_suite = load_suite(&suites, "Rays Suite");
	load_test(rays_suite, "Basic Ray Functionality", &test_ray);
	load_test(rays_suite, "Ray Position", &test_ray_pos);
	load_test(rays_suite, "Ray Intersection", &test_ray_intersect);
	load_test(rays_suite, "Aggregating Intersections",
		&test_aggregating_intersections);
	load_test(rays_suite, "Hit Detection", &test_hit);
	load_test(rays_suite, "Ray Transformation", &test_ray_transform);
	load_test(rays_suite, "Sphere Ray Transformation",
		&test_sphere_ray_transform);
	light_shading_suite = load_suite(&suites, "Light and Shading Suite");
	load_test(light_shading_suite, "Sphere Normalization",
		&test_sphere_normals);
	load_test(light_shading_suite, "Sphere Normal Transformation",
		&test_sphere_normal_transform);
	load_test(light_shading_suite, "Vector Reflection",
		&test_vector_reflection);
	load_test(light_shading_suite, "Light Struct", &test_light_struct);
	load_test(light_shading_suite, "Sphere Material", &test_sphere_material);
	load_test(light_shading_suite, "Sphere Lighiting", &test_sphere_lighting);
	rendering_suite = load_suite(&suites, "Rendering Suite");
	load_test(rendering_suite, "Default Scene", &test_default_scene);
	load_test(rendering_suite, "Intersect Scene", &test_intersect_scene);
	load_test(rendering_suite, "Prepare Computations", &test_prepare_computations);
	load_test(rendering_suite, "Shade Hit", &test_shade_hit);
	load_test(rendering_suite, "Color At", &test_color_at);
	load_test(rendering_suite, "View Transform", &test_view_transform);
	load_test(rendering_suite, "Camera", &test_camera);
	load_test(rendering_suite, "Ray For Pixel", &test_ray_for_pixel);
	load_test(rendering_suite, "Render Scene", &test_render_scene);
	shadow_suite = load_suite(&suites, "Shadows Suite");
	load_test(shadow_suite, "Lighting when Surface in Shadow", &test_shadow_surface);
	load_test(shadow_suite, "Testing is_shadowed() function", &test_shadow_is_shadowed);
	load_test(shadow_suite, "Testing updated shade_hit() function for shadows", &test_shadow_shade);
	load_test(shadow_suite, "Testing over_point update to t_comps", &test_shadow_point_offsets);
	planes_suite = load_suite(&suites, "Planes Suite");
	load_test(planes_suite, "Plane Default Attributes", &test_planes_default);
	load_test(planes_suite, "Plane Transformed Normal (i.e. updated normal_at()", &test_planes_updated_normal);
	load_test(planes_suite, "Planes and Rays without Intersections", &test_planes_no_intersections);
	load_test(planes_suite, "Planes and Rays with Intersections", &test_planes_intersections);
	cylinders_suite = load_suite(&suites, "Cylinders Suite");
	load_test(cylinders_suite, "Cylinders and Rays with Intersections", &test_cylinders_intersections);
	load_test(cylinders_suite, "Cylinders and Rays without Intersections", &test_cylinders_no_intersections);
	load_test(cylinders_suite, "Cylinder Transformed Normal", &test_cylinders_normal);
	load_test(cylinders_suite, "Cylinders Min-Max Defaults", &test_cylinders_min_max);
	load_test(cylinders_suite, "Cylinders Truncated Ends", &test_cylinders_truncated);
	load_test(cylinders_suite, "Cylinders Closed Cap Intersections", &test_cylinders_closed);
	load_test(cylinders_suite, "Cylinders End Cap Normals", &test_cylinders_cap_normals);
	cones_suite = load_suite(&suites, "Cones Suite");
	load_test(cones_suite, "Cone Ray Intersections", &test_cones_intersections);
	load_test(cones_suite, "Cone Parallel Ray Intersection", &test_cones_parallel_intersection);
	load_test(cones_suite, "Cone End Cap Intersections", &test_cones_end_caps);
	load_test(cones_suite, "Cone Normal Vector", &test_cones_normal);
	return (launch_tests(&suites));
}
