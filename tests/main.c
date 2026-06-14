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
	t_test_suite	*parser_suite;

	parser_suite = load_suite(&suites, "Tuples Suite");
	// parser_suite->setup = suite_setup;
	// parser_suite->teardown = suite_teardown;

	load_test(parser_suite, "Main Tuple Functionality", &test_t_tuple_values);
	load_test(parser_suite, "Tuple Utilities", &test_tuple_utils);
	load_test(parser_suite, "Tuple Addition", &test_tuple_addition);
	load_test(parser_suite, "Tuple Subtraction", &test_tuple_subtraction);

	return (launch_tests(&suites));
}
