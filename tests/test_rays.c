#include "../includes/scene.h"
#include "../includes/util/spheres.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/spheres.h"
#include <stdio.h>
#include <stdlib.h>
#include "ray.h"
#include "util/intersections.h"

int test_ray(void) {
	t_ray r;
	t_tuple origin = {1, 2, 3, POINT};
	t_tuple direction = {4, 5, 6, VECTOR};

	r.origin = origin;
	r.dir = direction;
	UNIT_ASSERT_EQ(compare_tuples(&(r.origin), &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&(r.dir), &direction), 0);

	return 0;
}

int test_ray_pos(void) {
	t_ray r = {.origin = {2, 3, 4, POINT}, .direction = {1, 0, 0, VECTOR}};

	t_point pos1 = position(r, 0);
	t_point pos2 = position(r, 1);
	t_point pos3 = position(r, -1);
	t_point pos4 = position(r, 2.5);

	t_point posA = {2, 3, 4, POINT};
	t_point posB = {3, 3, 4, POINT};
	t_point posC = {1, 3, 4, POINT};
	t_point posD = {4.5, 3, 4, POINT};

	UNIT_ASSERT_EQ(compare_tuples(&pos1, &posA), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos2, &posB), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos3, &posC), 0);
	UNIT_ASSERT_EQ(compare_tuples(&pos4, &posD), 0);

	return 0;
}

int test_ray_intersect(void) {
	t_sphere s = sphere_create();
	t_ray r;
	t_intersects	xS;

	// Scenario 0: A ray intersects a sphere at two points
	r.origin = (t_point){0, 0, -5, POINT};
	r.dir = (t_vector){0, 0, 1, VECTOR};
	xS = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 2);
	UNIT_ASSERT_FEQ(xS.list[0]->t, 4.0);
	UNIT_ASSERT_FEQ(xS.list[1]->t, 6.0);
	free_intersections(xS);

	// Scenario 1: A ray intersects a sphere at a tangent
	r.origin = (t_point){0, 1, -5, POINT};
	r.dir = (t_vector){0, 0, 1, VECTOR};
	xS = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 2);
	UNIT_ASSERT_FEQ(xS.list[0]->t, 5.0);
	UNIT_ASSERT_FEQ(xS.list[1]->t, 5.0);
	free_intersections(xS);

	// Scenario 2: A ray misses a sphere
	r.origin = (t_point){0, 2, -5, POINT};
	r.dir = (t_vector){0, 0, 1, VECTOR};
	xS = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 0);
	free_intersections(xS);

	// Scenario 3: A ray originates inside a sphere
	r.origin = (t_point){0, 0, 0, POINT};
	r.dir = (t_vector){0, 0, 1, VECTOR};
	xS = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 2);
	UNIT_ASSERT_FEQ(xS.list[0]->t, -1.0);
	UNIT_ASSERT_FEQ(xS.list[1]->t, 1.0);
	free_intersections(xS);

	// Scenario 4: A sphere is behind a ray
	r.origin = (t_point){0, 0, 5, POINT};
	r.dir = (t_vector){0, 0, 1, VECTOR};
	xS = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 2);
	UNIT_ASSERT_FEQ(xS.list[0]->t, -6.0);
	UNIT_ASSERT_FEQ(xS.list[1]->t, -4.0);
	free_intersections(xS);

	return (0);
}

int test_aggregating_intersections(void) {
	t_sphere s;
	t_intersect *i1;
	t_intersect *i2;
	t_intersects xs;

	s = sphere_create();
	i1 = create_intersection(SPHERE, &s, 1.0);
	i2 = create_intersection(SPHERE, &s, 2.0);
	xs = intersections_create();
	xs = intersections_add(xs, i1);
	xs = intersections_add(xs, i2);
	UNIT_ASSERT_EQ(intersections_len(xs), 2);
	UNIT_ASSERT_FEQ(xs.list[0]->t, 1.0);
	UNIT_ASSERT_FEQ(xs.list[1]->t, 2.0);
	UNIT_ASSERT_EQ(xs.list[0]->obj.ptr, &s);
	UNIT_ASSERT_EQ(xs.list[1]->obj.ptr, &s);
	free_intersections(xs);

	t_ray r = {.origin = {0, 0, -5, POINT}, .direction = {0, 0, 1, VECTOR}};
	t_sphere s1 = sphere_create();
	t_intersects xS = intersect_sphere(&s1, r);
	UNIT_ASSERT_EQ(intersections_len(xS), 2);
	UNIT_ASSERT_EQ(xS.list[0]->obj.ptr, &s1);
	UNIT_ASSERT_EQ(xS.list[1]->obj.ptr, &s1);
	free_intersections(xS);

	return (0);
}

int test_hit(void) {
	t_sphere s;
	t_intersect *i1;
	t_intersect *i2;
	t_intersects xS;
	t_intersect *i;

	s = sphere_create();
	i1 = create_intersection(SPHERE, &s, 1.0);
	i2 = create_intersection(SPHERE, &s, 2.0);
	xS = intersections_create();
	xS = intersections_add(xS, i1);
	xS = intersections_add(xS, i2);
	i = intersect_hit(xS);

	UNIT_ASSERT_EQ(i1->obj.ptr, i->obj.ptr);
	UNIT_ASSERT_FEQ(i1->t, i->t);

	free_intersections(xS);

	i1 = create_intersection(SPHERE, &s, -1.0);
	i2 = create_intersection(SPHERE, &s, 1.0);
	xS = intersections_create();
	xS = intersections_add(xS, i1);
	xS = intersections_add(xS, i2);
	i = intersect_hit(xS);

	UNIT_ASSERT_EQ(i2->obj.ptr, i->obj.ptr);
	UNIT_ASSERT_FEQ(i2->t, i->t);

	free_intersections(xS);

	i1 = create_intersection(SPHERE, &s, -2.0);
	i2 = create_intersection(SPHERE, &s, -1.0);
	xS = intersections_create();
	xS = intersections_add(xS, i1);
	xS = intersections_add(xS, i2);
	i = intersect_hit(xS);

	UNIT_ASSERT_EQ(NULL, i);

	free_intersections(xS);

	t_intersect *i3;
	t_intersect *i4;

	i1 = create_intersection(SPHERE, &s, 5.0);
	i2 = create_intersection(SPHERE, &s, 7.0);
	i3 = create_intersection(SPHERE, &s, -3.0);
	i4 = create_intersection(SPHERE, &s, 2.0);
	xS = intersections_create();
	xS = intersections_add(xS, i1);
	xS = intersections_add(xS, i2);
	xS = intersections_add(xS, i3);
	xS = intersections_add(xS, i4);
	i = intersect_hit(xS);

	UNIT_ASSERT_EQ(i4->obj.ptr, i->obj.ptr);
	UNIT_ASSERT_FEQ(i4->t, i->t);

	free_intersections(xS);

	return (0);
}

int	test_ray_transform(void)
{
	t_ray		r1;
	t_ray		r2;
	t_ray		t1;
	t_ray		t2;
	t_m4x4	m1;
	t_m4x4	m2;
	t_point		expected_origin1 = {4, 6, 8, POINT};
	t_vector	expected_direction1 = {0, 1, 0, VECTOR};
	t_point		expected_origin2 = {2, 6, 12, POINT};
	t_vector	expected_direction2 = {0, 3, 0, VECTOR};

	r1 = (t_ray){
		.origin = {1, 2, 3, POINT},
		.direction = {0, 1, 0, VECTOR}
	};

	m1 = m4x4_translation(3, 4, 5);
	t1 = transform(r1, m1);

	UNIT_ASSERT_EQ(compare_tuples(&(t1.origin), &expected_origin1), 0);
	UNIT_ASSERT_EQ(compare_tuples(&(t1.direction), &expected_direction1), 0);

	r2 = (t_ray){
		.origin = {1, 2, 3, POINT},
		.direction = {0, 1, 0, VECTOR}
	};
	m2 = m4x4_scaling(2, 3, 4);
	t2 = transform(r2, m2);

	UNIT_ASSERT_EQ(compare_tuples(&(t2.origin), &expected_origin2), 0);
	UNIT_ASSERT_EQ(compare_tuples(&(t2.direction), &expected_direction2), 0);

	return (0);
}

int	test_sphere_ray_transform(void)
{
	t_sphere		s;
	t_object		obj;
	t_m4x4		identity;
	t_m4x4		translation;
	t_ray			r;
	t_intersects	xs;

	s = sphere_create();
	obj = (t_object){SPHERE, &s};
	identity = m4x4_identity();
	UNIT_ASSERT_EQ(m4x4_compare(s.transform, identity), 0);

	translation = m4x4_translation(2, 3, 4);
	set_transform(&obj, translation);
	UNIT_ASSERT_EQ(m4x4_compare(s.transform, translation), 0);

	r = (t_ray){
		.origin = {0, 0, -5, POINT},
		.direction = {0, 0, 1, VECTOR}
	};
	s = sphere_create();
	obj = (t_object){SPHERE, &s};
	set_transform(&obj, m4x4_scaling(2, 2, 2));
	xs = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xs), 2);
	UNIT_ASSERT_FEQ(xs.list[0]->t, 3.0);
	UNIT_ASSERT_FEQ(xs.list[1]->t, 7.0);
	free_intersections(xs);

	r = (t_ray){
		.origin = {0, 0, -5, POINT},
		.direction = {0, 0, 1, VECTOR}
	};
	s = sphere_create();
	obj = (t_object){SPHERE, &s};
	set_transform(&obj, m4x4_translation(5, 0, 0));
	xs = intersect_sphere(&s, r);
	UNIT_ASSERT_EQ(intersections_len(xs), 0);
	free_intersections(xs);

	return (0);
}
