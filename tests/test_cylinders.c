#include "libunit.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/cylinders.h"
#include <math.h>

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

int	test_cylinders_min_max(void)
{
	t_cylinder	c = cylinder_create();

	/**
	 * apparently, comparing INFINITE to INFINITE using the UNIT_ASSERT_FEQ
	 * macro results in a NaN because of how the compiler subtracts these values
	 * if the flag -ffast-math, it becomes simplified to (a - a), which would make it pass
	 * 
	 * just note that INFINITE, like NaN, is not a float or a double, maybe it is? seems weird
	 */
	UNIT_ASSERT_EQ(c.max, INFINITY);
	UNIT_ASSERT_EQ(c.min, -INFINITY);

	return (0);
}

int	test_cylinders_truncated(void)
{
	t_cylinder	c = cylinder_create();
	c.min = 1.0;
	c.max = 2.0;

	t_point		point[6] = {{0, 1.5, 0, POINT}, {0, 3, -5, POINT}, {0, 0, -5, POINT},
		{0, 2, -5, POINT}, {0, 1, -5, POINT}, {0, 1.5, -2, POINT}};
	t_vector	dir[6] = {{0.1, 1, 0, VECTOR}, {0, 0, 1, VECTOR}, {0, 0, 1, VECTOR},
		{0, 0, 1, VECTOR}, {0, 0, 1, VECTOR}, {0, 0, 1, VECTOR}};
	int			count[6] = {0, 0, 0, 0, 0, 2};

	t_vector		d;
	t_ray			r;
	t_object		o = (t_object){CYLINDER, &c};
	t_intersections	xs;

	for (int i = 0; i < 6; i++)
	{
		d = calc_norm(dir[i]);
		r = ray(point[i], d);
		xs = intersect(&o, r);
		UNIT_ASSERT_EQ(xs.count, count[i]);
	}
	return (0);
}

int	test_cylinders_closed(void)
{
	t_cylinder	cyl = cylinder_create();

	UNIT_ASSERT_EQ(cyl.closed, 0);

	cyl.min = 1;
	cyl.max = 2;
	cyl.closed = 1;

	t_point	points[5] = {
		{0, 3, 0, POINT},
		{0, 3, -2, POINT},
		{0, 4, -2, POINT},
		{0, 0, -2, POINT},
		{0, -1, -2, POINT}
	};

	t_vector	directions[5] = {
		{0, -1, 0, VECTOR},
		{0, -1, 2, VECTOR},
		{0, -1, 1, VECTOR},
		{0, 1, 2, VECTOR},
		{0, 1, 1, VECTOR}
	};

	int	counts[5] = {2, 2, 2, 2, 2};

	t_intersections	xs;
	t_ray			r;
	t_object		obj = {CYLINDER, &cyl};

	for (int i = 0; i < 5; i++)
	{
		directions[i] = calc_norm(directions[i]);
		r = ray(points[i], directions[i]);
		xs = intersect(&obj, r);
		UNIT_ASSERT_EQ(xs.count, counts[i]);
	}

	return (0);
}

int	test_cylinders_cap_normals(void)
{
	t_cylinder	cyl = cylinder_create();

	cyl.min = 1;
	cyl.max = 2;
	cyl.closed = 1;

	t_point	points[6] = {
		{0, 1, 0, POINT},
		{0.5, 1, 0, POINT},
		{0, 1, 0.5, POINT},
		{0, 2, 0, POINT},
		{0.5, 2, 0, POINT},
		{0, 2, 0.5, POINT}
	};

	t_vector	expected_normals[6] = {
		{0, -1, 0, VECTOR},
		{0, -1, 0, VECTOR},
		{0, -1, 0, VECTOR},
		{0, 1, 0, VECTOR},
		{0, 1, 0, VECTOR},
		{0, 1, 0, VECTOR}
	};

	t_object	obj = {CYLINDER, &cyl};
	t_vector	res;

	for (int i = 0; i < 6; i++)
	{
		res = normal_at(&obj, points[i]);
		UNIT_ASSERT_EQ(compare_tuples(&res, &(expected_normals[i])), 0);
	}
	return (0);
}

