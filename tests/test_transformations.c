#include <math.h>
#include "libunit_assert.h"
#include "minirt.h"

int	test_translation(void)
{
	t_matrix4x4	transform;
	t_tuple		point;
	t_tuple		expected;
	t_tuple		result;

	transform = matrix4x4_translation(5.0, -3.0, 2.0);
	point = (t_tuple){-3.0, 4.0, 5.0, POINT};
	expected = (t_tuple){2.0, 1.0, 7.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	t_matrix4x4	inverse;

	transform = matrix4x4_translation(5.0, -3.0, 2.0);
	inverse = matrix4x4_inverse(transform);
	point = (t_tuple){-3.0, 4.0, 5.0, POINT};
	expected = (t_tuple){-8.0, 7.0, 3.0, POINT};

	result = matrix4x4_multiply_tuple(inverse, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	t_tuple	vector;

	transform = matrix4x4_translation(5.0, -3.0, 2.0);
	vector = (t_tuple){-3, 4, 5, VECTOR};

	result = matrix4x4_multiply_tuple(transform, vector);

	UNIT_ASSERT_EQ(compare_tuples(&vector, &result), 0);

	return (0);
}

int	test_scaling(void)
{
	t_matrix4x4	transform;
	t_tuple		point;
	t_tuple		expected;
	t_tuple		result;

	transform = matrix4x4_scaling(2.0, 3.0, 4.0);
	point = (t_tuple){-4.0, 6.0, 8.0, POINT};
	expected = (t_tuple){-8.0, 18.0, 32.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	t_tuple	vector;

	transform = matrix4x4_scaling(2.0, 3.0, 4.0);
	vector = (t_tuple){-4.0, 6.0, 8.0, VECTOR};
	expected = (t_tuple){-8.0, 18.0, 32.0, VECTOR};

	result = matrix4x4_multiply_tuple(transform, vector);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	t_matrix4x4	inverse;

	transform = matrix4x4_scaling(2.0, 3.0, 4.0);
	inverse = matrix4x4_inverse(transform);
	vector = (t_tuple){-4.0, 6.0, 8.0, VECTOR};
	expected = (t_tuple){-2.0, 2.0, 2.0, VECTOR};

	result = matrix4x4_multiply_tuple(inverse, vector);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_scaling(-1.0, 1.0, 1.0);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){-2.0, 3.0, 4.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	return (0);
}

int	test_rotation(void)
{
	t_matrix4x4	transform;
	t_tuple		point;
	t_tuple		expected;
	t_tuple		result;

	transform = matrix4x4_rotation_x(PI / 4.0);
	point = (t_tuple){0.0, 1.0, 0.0, POINT};
	expected = (t_tuple){0.0, sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_rotation_x(PI / 2.0);
	point = (t_tuple){0.0, 1.0, 0.0, POINT};
	expected = (t_tuple){0.0, 0.0, 1.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_inverse(matrix4x4_rotation_x(PI / 4.0));
	point = (t_tuple){0.0, 1.0, 0.0, POINT};
	expected = (t_tuple){0.0, sqrt(2.0) / 2.0, -sqrt(2.0) / 2.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_rotation_y(PI / 4.0);
	point = (t_tuple){0.0, 0.0, 1.0, POINT};
	expected = (t_tuple){sqrt(2.0) / 2.0, 0.0, sqrt(2.0) / 2.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_rotation_y(PI / 2.0);
	point = (t_tuple){0.0, 0.0, 1.0, POINT};
	expected = (t_tuple){1.0, 0.0, 0.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_rotation_z(PI / 4.0);
	point = (t_tuple){0.0, 1.0, 0.0, POINT};
	expected = (t_tuple){-sqrt(2.0) / 2.0, sqrt(2.0) / 2.0, 0.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_rotation_z(PI / 2.0);
	point = (t_tuple){0.0, 1.0, 0.0, POINT};
	expected = (t_tuple){-1.0, 0.0, 0.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	return (0);
}

int	test_shearing(void)
{
	t_matrix4x4	transform;
	t_tuple		point;
	t_tuple		expected;
	t_tuple		result;
	double		p1[6] = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0};
	double		p2[6] = {0.0, 1.0, 0.0, 0.0, 0.0, 0.0};
	double		p3[6] = {0.0, 0.0, 1.0, 0.0, 0.0, 0.0};
	double		p4[6] = {0.0, 0.0, 0.0, 1.0, 0.0, 0.0};
	double		p5[6] = {0.0, 0.0, 0.0, 0.0, 1.0, 0.0};
	double		p6[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 1.0};

	transform = matrix4x4_shearing(p1);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){5.0, 3.0, 4.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_shearing(p2);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){6.0, 3.0, 4.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_shearing(p3);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){2.0, 5.0, 4.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_shearing(p4);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){2.0, 7.0, 4.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_shearing(p5);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){2.0, 3.0, 6.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	transform = matrix4x4_shearing(p6);
	point = (t_tuple){2.0, 3.0, 4.0, POINT};
	expected = (t_tuple){2.0, 3.0, 7.0, POINT};

	result = matrix4x4_multiply_tuple(transform, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	return (0);
}

int	test_chaining(void)
{
	t_matrix4x4	rotation;
	t_matrix4x4	scaling;
	t_matrix4x4	translation;
	t_tuple		point;
	t_tuple		expected;
	t_tuple		result;

	rotation = matrix4x4_rotation_x(PI / 2.0);
	scaling = matrix4x4_scaling(5.0, 5.0, 5.0);
	translation = matrix4x4_translation(10.0, 5.0, 7.0);

	point = (t_tuple){1.0, 0.0, 1.0, POINT};
	expected = (t_tuple){1.0, -1.0, 0.0, POINT};

	result = matrix4x4_multiply_tuple(rotation, point);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	expected = (t_tuple){5.0, -5.0, 0.0, POINT};

	result = matrix4x4_multiply_tuple(scaling, result);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	expected = (t_tuple){15.0, 0.0, 7.0, POINT};

	result = matrix4x4_multiply_tuple(translation, result);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	rotation = matrix4x4_rotation_x(PI / 2.0);
	scaling = matrix4x4_scaling(5.0, 5.0, 5.0);
	translation = matrix4x4_translation(10.0, 5.0, 7.0);
	point = (t_tuple){1.0, 0.0, 1.0, POINT};
	expected = (t_tuple){15.0, 0.0, 7.0, POINT};

	result = matrix4x4_multiply_tuple(translation, matrix4x4_multiply_tuple(scaling, matrix4x4_multiply_tuple(rotation, point)));

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	return (0);
}
