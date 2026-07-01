#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/spheres.h"
#include <math.h>


int	test_sphere_normals(void)
{
	t_sphere	s;
	t_vector	v;
	t_vector	expected;

	s = sphere_create();
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

int	test_sphere_normal_transform(void)
{
	t_sphere s;
	t_vector expected = vector(0, 0.70711, -0.70711);

	s = sphere_create();
	set_transform(&s, matrix4x4_translation(0, 1, 0));
	t_vector n = normal_at(&s, point(0, 1.70711, -0.70711));

	UNIT_ASSERT_EQ(compare_tuples(&n, &expected), 0);

	t_matrix4x4 m = matrix4x4_multiply(matrix4x4_scaling(1, 0.5, 1),
			matrix4x4_rotation_z(PI / 5));
	set_transform(&s, m);

	expected = vector(0, 0.97014, -0.24254);
	n = normal_at(&s, point(0, sqrt(2) / 2, -(sqrt(2) / 2)));

	UNIT_ASSERT_EQ(compare_tuples(&n, &expected), 0);


	return (0);
}
