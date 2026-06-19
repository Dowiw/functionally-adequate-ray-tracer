#include "minirt.h"
#include <math.h>

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

/**
 * @brief Clamps the double color into an integer
 * 
 * @param color color value
 * @return int color integer
 */
int	clamp_color(double color)
{
	double	c_d;
	int		c;

	c_d = round(color * 255);
	c = (int)c_d;
	if (c < 0)
		return (0);
	if (c > 255)
		return (255);
	return (c);
}