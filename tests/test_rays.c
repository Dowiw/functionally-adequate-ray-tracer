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
	t_intersect	xs;

	// Scenario 0: A ray intersects a sphere at two points
	r.origin = (t_point){0, 0, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.times[0], 4.0);
	UNIT_ASSERT_FEQ(xs.times[1], 6.0);
	
	// Scenario 1: A ray intersects a sphere at a tangent
	r.origin = (t_point){0, 1, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.times[0], 5.0);
	UNIT_ASSERT_FEQ(xs.times[1], 5.0);
	free(xs.times);

	// Scenario 2: A ray misses a sphere
	r.origin = (t_point){0, 2, -5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(s, r);
	UNIT_ASSERT_EQ(xs.count, 0);
	UNIT_ASSERT_EQ(xs.times, NULL);
	free(xs.times);

	// Scenario 3: A ray originates inside a sphere
	r.origin = (t_point){0, 0, 0, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.times[0], -1.0);
	UNIT_ASSERT_FEQ(xs.times[1], 1.0);
	free(xs.times);

	// Scenario 4: A sphere is behind a ray
	r.origin = (t_point){0, 0, 5, POINT};
	r.direction = (t_vector){0, 0, 1, VECTOR};
	xs = intersect(s, r);
	UNIT_ASSERT_EQ(xs.count, 2);
	UNIT_ASSERT_FEQ(xs.times[0], -6.0);
	UNIT_ASSERT_FEQ(xs.times[1], -4.0);
	free(xs.times);

	return (0);
}