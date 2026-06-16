#include "libunit_assert.h"
#include "minirt.h"

// Assuming a color_mult function will be implemented to handle color-by-color multiplication.
t_tuple	color_mult(const t_tuple a, const t_tuple b);

int	test_color(void)
{
	t_tuple	c = {-0.5, 0.4, 1.7, COLOR};
	UNIT_ASSERT_FEQ(c.x, -0.5);
	UNIT_ASSERT_FEQ(c.y, 0.4);
	UNIT_ASSERT_FEQ(c.z, 1.7);
	UNIT_ASSERT_FEQ(c.w, COLOR);
	return (0);
}

int	test_color_add(void)
{
	t_tuple	c1 = {0.9, 0.6, 0.75, COLOR};
	t_tuple	c2 = {0.7, 0.1, 0.25, COLOR};
	t_tuple	res;

	res = tuples_add(c1, c2);
	UNIT_ASSERT_FEQ(res.x, 1.6);
	UNIT_ASSERT_FEQ(res.y, 0.7);
	UNIT_ASSERT_FEQ(res.z, 1.0);
	return (0);
}

int	test_color_sub(void)
{
	t_tuple	c1 = {0.9, 0.6, 0.75, COLOR};
	t_tuple	c2 = {0.7, 0.1, 0.25, COLOR};
	t_tuple	res;

	res = tuples_sub(c1, c2);
	UNIT_ASSERT_FEQ(res.x, 0.2);
	UNIT_ASSERT_FEQ(res.y, 0.5);
	UNIT_ASSERT_FEQ(res.z, 0.5);
	return (0);
}

int	test_color_mult_scalar(void)
{
	t_tuple	c = {0.2, 0.3, 0.4, COLOR};
	t_tuple	res;

	res = tuple_mult(c, 2.0);
	UNIT_ASSERT_FEQ(res.x, 0.4);
	UNIT_ASSERT_FEQ(res.y, 0.6);
	UNIT_ASSERT_FEQ(res.z, 0.8);
	return (0);
}

int	test_color_mult(void)
{
	t_tuple	c1 = {1.0, 0.2, 0.4, COLOR};
	t_tuple	c2 = {0.9, 1.0, 0.1, COLOR};
	t_tuple	res;

	res = shur_prod(c1, c2);
	UNIT_ASSERT_FEQ(res.x, 0.9);
	UNIT_ASSERT_FEQ(res.y, 0.2);
	UNIT_ASSERT_FEQ(res.z, 0.04);
	return (0);
}