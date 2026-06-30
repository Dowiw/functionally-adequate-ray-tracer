#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/spheres.h"
#include <math.h>

int	test_sphere_normals(void)
{
	t_sphere	s = sphere_create();
	t_vector	v;
	t_vector	expected;

	v = normal_at(&s, point(1, 0, 0));
	expected = vector(1, 0, 0);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);

	v = normal_at(&s, point(0, 1, 0));
	expected = vector(0, 1, 0);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);

	v = normal_at(&s, point(0, 0, 1));
	expected = vector(0, 0, 1);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);

	v = normal_at(&s, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	expected = vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);

	return (0);
}