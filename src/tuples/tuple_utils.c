#include "minirt.h"
#include <math.h>

/**
 * @brief Calculates the magnitude of a vector.
 * NOTE: Assumes that the tuple is already a vector.
 *
 * @param a
 * @return the magnitude
 */
double	calc_mag(const t_tuple a)
{
	double	mag;

	mag = sqrt(pow(a.x, 2.0) + pow(a.y, 2.0) + pow(a.z, 2.0) + pow(a.w, 2.0));
	return (mag);
}

/**
 * @brief Calculates the unit vector of an arbitrary vector.
 * NOTE: Assumes that the tuple is already a vector.
 *
 * @param a
 * @return normalized vector
 */
t_tuple	calc_norm(const t_tuple a)
{
	t_tuple	normed;
	double	mag;

	mag = calc_mag(a);
	normed.x = a.x / mag;
	normed.y = a.y / mag;
	normed.z = a.z / mag;
	normed.w = a.w / mag;
	return (normed);
}

/**
 * @brief Calculates the dot product of two vectors.
 * NOTE: Assumes that the tuples are vectors.
 *
 * @param a
 * @param b
 * @return the dot product (scalar value)
 */
double	dot_product(const t_tuple a, const t_tuple b)
{
	double	dot;

	dot = 0.0;
	dot += (a.x * b.x);
	dot += (a.y * b.y);
	dot += (a.z * b.z);
	dot += (a.w * b.w);
	return (dot);
}

/**
 * @brief Calculates the cross product of two vectors.
 * NOTE: Assumes that the tuples are vectors
 *
 * @param a
 * @param b
 * @return the cross product (vector)
 */
t_tuple	cross_product(const t_tuple a, const t_tuple b)
{
	t_tuple	cross;

	cross.x = (a.x * b.z - a.z * b.y);
	cross.y = (a.z * b.x - a.x * b.z);
	cross.z = (a.x * b.y - a.y * b.x);
	cross.w = VECTOR;
	return (cross);
}
