#include "libunit.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/planes.h"
#include "ray.h"
#include <X11/Xlib.h>
#include <math.h>

int	test_planes_default(void)
{
	t_plane		p;
	t_object	obj;
	t_matrix4x4	identity;
	t_material	m;

	p = plane_create();
	obj = (t_object){PLANE, &p};
	identity = matrix4x4_identity();
	UNIT_ASSERT_EQ(matrix4x4_compare(identity, p.transform), 0);

	set_transform(&obj, matrix4x4_translation(2, 3, 4));
	UNIT_ASSERT_EQ(matrix4x4_compare(p.transform, matrix4x4_translation(2, 3, 4)), 0);

	m = material();
	m.ambient = 1;
	p.material = m;
	UNIT_ASSERT_FEQ(m.ambient, p.material.ambient);

	return (0);
}

int	test_planes_updated_normal(void)
{
	t_plane		p;
	t_object	obj;
	t_vector	n;
	t_vector	expected;
	t_matrix4x4	m;

	p = plane_create();
	obj = (t_object){PLANE, &p};
	set_transform(&obj, matrix4x4_translation(0, 1, 0));
	n = normal_at(&obj, point(0, 1.70711, -0.70711));
	expected = vector(0, 1, 0);
	UNIT_ASSERT_EQ(compare_tuples(&n, &expected), 0);

	p = plane_create();
	obj = (t_object){PLANE, &p};
	m = matrix4x4_multiply(matrix4x4_scaling(1, 0.5, 1),
			matrix4x4_rotation_z(PI / 5));
	set_transform(&obj, m);
	n = normal_at(&obj, point(0, sqrt(2) / 2, -(sqrt(2) / 2)));
	expected = vector(-0.34144, 0.93991, 0);
	UNIT_ASSERT_FEQ(n.x, expected.x);
	UNIT_ASSERT_FEQ(n.y, expected.y);
	UNIT_ASSERT_FEQ(n.z, expected.z);

	return (0);
}

int	test_planes_constant_size(void)
{
	t_plane		p;
	t_object	o;

	p = plane_create();
	o = (t_object){PLANE, &p};
	t_vector n1 = normal_at(&o, point(0, 0, 0));
	t_vector n2 = normal_at(&o, point(10, 0, -10));
	t_vector n3 = normal_at(&o, point(-5, 0, 150));

	t_vector	exp = vector(0, 1, 0);
	UNIT_ASSERT_EQ(compare_tuples(&n1, &exp), 0);
	UNIT_ASSERT_EQ(compare_tuples(&n2, &exp), 0);
	UNIT_ASSERT_EQ(compare_tuples(&n3, &exp), 0);

	return (0);
}

int	test_planes_no_intersections(void)
{
	t_plane		p = plane_create();
	t_ray		r = ray(point(0, 10, 0), vector(0, 0, 1));
	t_object	o = (t_object){PLANE, &p};

	t_intersections	xs = intersect(&o, r);
	UNIT_ASSERT_EQ(xs.count, 0);

	t_ray	r2 = ray(point(0, 0, 0), vector(0, 0, 1));
	xs = intersect(&o, r2);
	UNIT_ASSERT_EQ(xs.count, 0);

	return (0);
}

int	test_planes_intersections(void)
{
	t_plane		p = plane_create();
	t_ray		r = ray(point(0, 1, 0), vector(0, -1, 0));
	t_object	o = (t_object){PLANE, &p};

	t_intersections	xs = intersect(&o, r);
	UNIT_ASSERT_EQ(xs.count, 1);
	UNIT_ASSERT_FEQ(xs.list[0]->t, 1);
	UNIT_ASSERT_EQ(xs.list[0]->obj.object, &p);

	t_ray		r2 = ray(point(0, -1, 0), vector(0, 1, 0));
	xs = intersect(&o, r2);
	UNIT_ASSERT_EQ(xs.count, 1);
	UNIT_ASSERT_FEQ(xs.list[0]->t, 1);
	UNIT_ASSERT_EQ(xs.list[0]->obj.object, &p);
	
	return (0);
}
