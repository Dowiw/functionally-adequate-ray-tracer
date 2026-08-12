#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/spheres.h"
#include <math.h>

int	test_sphere_normals(void)
{
	t_sphere	s;
	t_object	obj;
	t_vector	v;
	t_vector	expected;

	s = sphere_create();
	obj = (t_object){SPHERE, &s};
	v = normal_at(&obj, point(1, 0, 0));
	expected = vector(1, 0, 0);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);
	v = normal_at(&obj, point(0, 1, 0));
	expected = vector(0, 1, 0);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);
	v = normal_at(&obj, point(0, 0, 1));
	expected = vector(0, 0, 1);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);
	v = normal_at(&obj, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));
	expected = vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
	UNIT_ASSERT_EQ(compare_tuples(&v, &expected), 0);
	return (0);
}

int	test_sphere_normal_transform(void)
{
	t_sphere	s;
	t_object	obj;
	t_vector	expected;
	t_vector	n;
	t_matrix4x4	m;

	expected = vector(0, 0.70711, -0.70711);
	s = sphere_create();
	obj = (t_object){SPHERE, &s};
	set_transform(&obj, matrix4x4_translation(0, 1, 0));
	n = normal_at(&obj, point(0, 1.70711, -0.70711));
	UNIT_ASSERT_EQ(compare_tuples(&n, &expected), 0);
	m = matrix4x4_multiply(matrix4x4_scaling(1, 0.5, 1), matrix4x4_rotation_z(PI
				/ 5));
	set_transform(&obj, m);
	expected = vector(0, 0.97014, -0.24254);
	n = normal_at(&obj, point(0, sqrt(2) / 2, -(sqrt(2) / 2)));
	UNIT_ASSERT_EQ(compare_tuples(&n, &expected), 0);
	return (0);
}

int	test_vector_reflection(void)
{
	t_vector	v1;
	t_vector	n1;
	t_vector	r1;
	t_vector	e1;

	v1 = vector(1, -1, 0);
	n1 = vector(0, 1, 0);
	r1 = reflect(v1, n1);
	e1 = vector(1, 1, 0);
	UNIT_ASSERT_EQ(compare_tuples(&e1, &r1), 0);
	v1 = vector(0, -1, 0);
	n1 = vector(sqrt(2) / 2, sqrt(2) / 2, 0);
	r1 = reflect(v1, n1);
	e1 = vector(1, 0, 0);
	UNIT_ASSERT_EQ(compare_tuples(&e1, &r1), 0);
	return (0);
}

int	test_light_struct(void)
{
	t_color	intensity;
	t_point	pos;
	t_light	l;

	intensity = color(1, 1, 1);
	pos = point(0, 0, 0);
	l.pos = pos;
	l.intensity = intensity;
	UNIT_ASSERT_EQ(compare_tuples(&l.pos, &pos), 0);
	UNIT_ASSERT_EQ(compare_tuples(&l.intensity, &intensity), 0);
	return (0);
}

int	compare_materials(const t_material *a, const t_material *b)
{
	if (compare_tuples(&a->color, &b->color) != 0)
		return (1);
	if (compare_doubles(a->ambient, b->ambient) != 0)
		return (1);
	if (compare_doubles(a->diffuse, b->diffuse) != 0)
		return (1);
	if (compare_doubles(a->specular, b->specular) != 0)
		return (1);
	if (compare_doubles(a->shininess, b->shininess) != 0)
		return (1);
	return (0);
}

int	test_sphere_material(void)
{
	t_material	m;
	t_color		c;
	t_sphere	s;

	c = (t_color){.x = 1, .y = 1, .z = 1, .w = COLOR};
	m = material();
	UNIT_ASSERT_EQ(compare_tuples(&m.color, &c), 0);
	UNIT_ASSERT_FEQ(m.ambient, 0.1);
	UNIT_ASSERT_FEQ(m.diffuse, 0.9);
	UNIT_ASSERT_FEQ(m.specular, 0.9);
	UNIT_ASSERT_FEQ(m.shininess, 200.0);
	s = sphere_create();
	UNIT_ASSERT_EQ(compare_materials(&s.material, &m), 0);
	m.ambient = 1.0;
	s.material = m;
	UNIT_ASSERT_FEQ(s.material.ambient, m.ambient);
	return (0);
}

int	test_sphere_lighting(void)
{
	t_material	m;
	t_point		pos;
	t_vector	eyev;
	t_vector	normalv;
	t_light		light_p;
	t_color		res;
	t_color		expected_res;

	m = material();
	pos = point(0, 0, 0);
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light_p = light(point(0, 0, -10), color(1, 1, 1));
	res = lighting(m, light_p, pos, eyev, normalv, 0);
	expected_res = color(1.9, 1.9, 1.9);
	UNIT_ASSERT_EQ(compare_tuples(&res, &expected_res), 0);
	//
	eyev = vector(0, sqrt(2) / 2, sqrt(2) / 2);
	normalv = vector(0, 0, -1);
	light_p = light(point(0, 0, -10), color(1, 1, 1));
	res = lighting(m, light_p, pos, eyev, normalv, 0);
	expected_res = color(1, 1, 1);
	UNIT_ASSERT_EQ(compare_tuples(&res, &expected_res), 0);
	//
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light_p = light(point(0, 10, -10), color(1, 1, 1));
	res = lighting(m, light_p, pos, eyev, normalv, 0);
	expected_res = color(0.7364, 0.7364, 0.7364);
	UNIT_ASSERT_EQ(compare_tuples(&res, &expected_res), 0);
	//
	eyev = vector(0, -(sqrt(2) / 2), -(sqrt(2) / 2));
	normalv = vector(0, 0, -1);
	light_p = light(point(0, 10, -10), color(1, 1, 1));
	res = lighting(m, light_p, pos, eyev, normalv, 0);
	expected_res = color(1.6364, 1.6364, 1.6364);
	UNIT_ASSERT_EQ(compare_tuples(&res, &expected_res), 0);
	//
	eyev = vector(0, 0, -1);
	normalv = vector(0, 0, -1);
	light_p = light(point(0, 0, 10), color(1, 1, 1));
	res = lighting(m, light_p, pos, eyev, normalv, 0);
	expected_res = color(0.1, 0.1, 0.1);
	UNIT_ASSERT_EQ(compare_tuples(&res, &expected_res), 0);
	return (0);
}
