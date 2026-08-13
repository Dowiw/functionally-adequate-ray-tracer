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
	return (0);
}