#include "libunit_assert.h"
#include "minirt.h"
#include "scene.h"
#include "util/spheres.h"
#include <stdlib.h>
#include <stdio.h>

int test_ray(void) {
	t_ray r;
	t_tuple origin = {1, 2, 3, POINT};
	t_tuple direction = {4, 5, 6, VECTOR};

	r.origin = origin;
	r.direction = direction;
	UNIT_ASSERT_EQ(compare_tuples(&(r.origin), &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&(r.direction), &direction), 0);

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

int	test_ray_intersect(void)
{
	t_sphere	s = sphere_create();
	t_ray		r;
	t_intersections	xs;

	// Scenario 0: A ray intersects a sphere at two points
	r.origin = (t_point){0, 0, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(&s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.list[0].t, 4.0);
	UNIT_ASSERT_FEQ(xs.list[1].t, 6.0);
	
	// Scenario 1: A ray intersects a sphere at a tangent
	r.origin = (t_point){0, 1, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(&s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.list[0].t, 5.0);
	UNIT_ASSERT_FEQ(xs.list[1].t, 5.0);
	free(xs.list);

	// Scenario 2: A ray misses a sphere
	r.origin = (t_point){0, 2, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(&s, r);
	UNIT_ASSERT_EQ(xs.count, 0);
	UNIT_ASSERT_EQ(xs.list, NULL);

	// Scenario 3: A ray originates inside a sphere
	r.origin = (t_point){0, 0, 0, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(&s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.list[0].t, -1.0);
	UNIT_ASSERT_FEQ(xs.list[1].t, 1.0);
	free(xs.list);

	// Scenario 4: A sphere is behind a ray
	r.origin = (t_point){0, 0, 5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(&s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.list[0].t, -6.0);
	UNIT_ASSERT_FEQ(xs.list[1].t, -4.0);
	free(xs.list);

	return (0);
}

int	test_aggregating_intersections(void)
{
	t_sphere		s;
	t_intersection	i1;
	t_intersection	i2;
	t_intersections	xs;

	s = sphere_create();
	i1 = intersection(1.0, &s);
	i2 = intersection(2.0, &s);
	xs = intersections(2, i1, i2);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.list[0].t, 1.0);
	UNIT_ASSERT_FEQ(xs.list[1].t, 2.0);
	UNIT_ASSERT_EQ(xs.list[0].obj, &s);
	UNIT_ASSERT_EQ(xs.list[1].obj, &s);
	free(xs.list);

	t_ray r = { 
		.origin = {0, 0, -5, POINT}, 
		.direction = {0, 0, 1, VECTOR}
	};
	t_sphere s1 = sphere_create();
	t_intersections xS = intersect(&s1, r);
	UNIT_ASSERT_EQ(xS.count, 2);
	UNIT_ASSERT_EQ(xS.list[0].obj, &s1);
	UNIT_ASSERT_EQ(xS.list[1].obj, &s1);

	return (0);
}