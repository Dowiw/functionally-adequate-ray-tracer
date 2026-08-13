#include "libunit.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/cylinders.h"

int test_cylinders_no_intersections(void)
{
	t_cylinder c;
	t_point o[3] = {{1, 0, 0, POINT}, {0, 0, 0, POINT}, {0, 0, -5, POINT}};
	t_vector d[3] = {{0, 1, 0, VECTOR}, {0, 1, 0, VECTOR}, {1, 1, 1, VECTOR}};

	t_vector direction;
	t_ray r;

	c = cylinder_create();
	direction = calc_norm(d[0]);
	r = ray(o[0], direction);

	t_object obj = (t_object){CYLINDER, &c};
	t_intersections xs = intersect(&obj, r);

	UNIT_ASSERT_EQ(xs.count, 0);

	direction = calc_norm(d[1]);
	r = ray(o[1], direction);
	xs = intersect(&obj, r);

	UNIT_ASSERT_EQ(xs.count, 0);

	direction = calc_norm(d[2]);
	r = ray(o[2], direction);
	xs = intersect(&obj, r);

	UNIT_ASSERT_EQ(xs.count, 0);

	return (0);
}

int test_cylinders_intersections(void)
{
	t_cylinder	c = cylinder_create();

	t_point		o[3] = {{1, 0, -5, POINT}, {0, 0, -5, POINT}, {0.5, 0, -5, POINT}};
	t_vector	d[3] = {{0, 0, 1, VECTOR}, {0, 0, 1, VECTOR}, {0.1, 1, 1, VECTOR}};
	double	t0[3] = {5, 4, 6.80798};
	double	t1[3] = {5, 6, 7.08872};
	t_vector	direction;
	t_ray		r;
	t_intersections	xs;
	t_object	obj = (t_object){CYLINDER, &c};

	for (int i = 0; i < 3; i++)
	{
		direction = calc_norm(d[i]);
		r = ray(o[i], direction);
		xs = intersect(&obj, r);
		UNIT_ASSERT_EQ(xs.count, 2);
		UNIT_ASSERT_FEQ(xs.list[0]->t, t0[i]);
		UNIT_ASSERT_FEQ(xs.list[1]->t, t1[i]);
	}

	return (0);
}

int	test_cylinders_normal(void)
{
	t_cylinder	c = cylinder_create();
	t_point		p[4] = {{1, 0, 0, POINT}, {0, 5, -1, POINT}, {0, -2, 1, POINT}, {-1, 1, 0, POINT}};
	t_vector	expected_normal[4] = {{1, 0, 0, VECTOR}, {0, 0, -1, VECTOR}, {0, 0, 1, VECTOR}, {-1, 0, 0, VECTOR}};
	t_object	obj = (t_object){CYLINDER, &c};
	t_vector	res;

	for (int i = 0; i < 4; i++)
	{
		res = normal_at(&obj, p[i]);
		UNIT_ASSERT_EQ(compare_tuples(&res, &(expected_normal[i])), 0);
	}
	return (0);
}