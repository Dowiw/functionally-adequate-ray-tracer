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
	t_test_suite	*suites = NULL;
	t_test_suite	*tuple_suite;
	t_test_suite	*color_suite;

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
	load_test(color_suite, "Color Scalar Multiplication", &test_color_mult_scalar);
	load_test(color_suite, "Color Multiplication (Hadamard)", &test_color_mult);

	return (launch_tests(&suites));
}
