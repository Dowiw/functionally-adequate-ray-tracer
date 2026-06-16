#include "minirt.h"

/**
 * @brief Compare two doubles if they are equal
 *
 * @param a
 * @param b
 * @returns 0 on success, 1 on fail
 */
int	compare_doubles(const double a, const double b)
{
	if ((a - b) < UNIT_EPSILON && (b - a) < UNIT_EPSILON)
		return (0);
	return (1);
}

/**
 * @brief Compare two tuples if they are equal
 *
 * @param a
 * @param b
 * @returns 0 in success, 1 in failure
 */
int	compare_tuples(const t_tuple *a, const t_tuple *b)
{
	if (compare_doubles(a->x, b->x) == 0
		&& compare_doubles(a->y, b->y) == 0
		&& compare_doubles(a->z, b->z) == 0
		&& compare_doubles(a->w, b->w) == 0)
		return (0);
	return (1);
}