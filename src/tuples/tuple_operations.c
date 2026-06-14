#include "minirt.h"

/**
 * @brief Add two tuples (a + b) and returns sum
 * 
 * The type of the sum is based on the type of the input tuples:
 * - POINT + POINT = INVALID_POS
 * - POINT + VECTOR = POINT
 * - VECTOR + POINT = POINT
 * - VECTOR + VECTOR = VECTOR
 * 
 * @param a tuple a
 * @param b tuple b
 *
 * @returns the sum by value
 */
t_tuple	add_tuples(const t_tuple a, const t_tuple b)
{
	t_tuple	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	sum.w = a.w + b.w;
	return (sum);
}

/**
 * @brief Subtract two tuples (a - b) and returns difference
 * 
 * The type of the difference is based on the type of the input tuples:
 * - POINT - POINT = VECTOR
 * - POINT - VECTOR = POINT
 * - VECTOR - POINT = INVALID_NEG
 * - VECTOR - VECTOR = VECTOR
 * 
 * @param a tuple a
 * @param b tuple b
 * 
 * @returns the difference by value
 */
t_tuple sub_tuples(const t_tuple a, const t_tuple b)
{
	t_tuple diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	diff.w = a.w - b.w;
	return (diff);
}