#include "libunit_assert.h"
#include "minirt.h"

int	test_ray(void)
{
	t_ray	r;
	t_tuple	origin = {1, 2, 3, POINT};
	t_tuple	direction = {4, 5, 6, VECTOR};

	r.origin = origin;
	r.direction = direction;
	UNIT_ASSERT_EQ(compare_tuples(&(r.origin), &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&(r.direction), &direction), 0);

	return 0;
}

int	test_ray_pos(void)
{
	t_ray	r = { .origin = {2, 3, 4, POINT}, .direction = {1, 0, 0, VECTOR}};

	t_point	pos1 = position(r, 0);
	t_point	pos2 = position(r, 1);
	t_point	pos3 = position(r, -1);
	t_point	pos4 = position(r, 2.5);

	t_point	posA = {2, 3, 4, POINT};
	t_point	posB = {3, 3, 4, POINT};
	t_point	posC = {1, 3, 4, POINT};
	t_point	posD = {4.5, 3, 4, POINT};

	UNIT_ASSERT_EQ(compare_tuples(&pos1, &posA), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos2, &posB), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos3, &posC), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos4, &posD), 0);

	return 0;
}