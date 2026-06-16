#include "minirt.h"

/**
 * @brief Calculates the blending of two colors to form a new color
 * NOTE: Assumes the tuples are colors
 * 
 * @param color_a
 * @param color_b
 * @return resulting blended color
 */
t_tuple	shur_prod(const t_tuple color_a, const t_tuple color_b)
{
	t_tuple	prod;

	prod.x = color_a.x * color_b.x;
	prod.y = color_a.y * color_b.y;
	prod.z = color_a.z * color_b.z;
	prod.w = COLOR;
	return (prod);
}