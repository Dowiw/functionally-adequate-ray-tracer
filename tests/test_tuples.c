#include "libunit.h"
#include "minirt.h"

int	test_t_tuple_values(void)
{
	t_tuple	vector;

	vector.x = 1.0;
	vector.y = 0.5;
	vector.z = 2.0;
	vector.type = VECTOR;

	UNIT_ASSERT_FEQ(vector.x, 1.0);
	UNIT_ASSERT_FEQ(vector.y, 0.5);
	UNIT_ASSERT_FEQ(vector.z, 2.0);
	UNIT_ASSERT_EQ(vector.type, VECTOR);

	t_tuple	point;

	point.x = 12.1;
	point.y = 10.3;
	point.z = 0.4;
	point.type = POINT;

	UNIT_ASSERT_FEQ(point.x, 12.1);
	UNIT_ASSERT_FEQ(point.y, 10.3);
	UNIT_ASSERT_FEQ(point.z, 0.4);
	UNIT_ASSERT_EQ(point.type, POINT);

	return (0);
}

int	test_tuple_utils(void)
{
	UNIT_ASSERT_EQ(compare_doubles(1.0, 1.0), 0);

	t_tuple	a = {1.0, 2.0, 3.0, POINT};
	t_tuple	b = {1.0, 2.0, 3.0, POINT};

	UNIT_ASSERT_EQ(compare_tuples(&a, &b), 0);
	return (0);
}

int	test_tuple_addition(void)
{
	t_tuple a = {3, -2, 5, POINT};
	t_tuple b = {-2, 3, 1, VECTOR};
	t_tuple result;

	result = add_tuples(a, b);
	UNIT_ASSERT_FEQ(result.x, 1.0);
	UNIT_ASSERT_FEQ(result.y, 1.0);
	UNIT_ASSERT_FEQ(result.z, 6.0);
	UNIT_ASSERT_EQ(result.type, POINT);

	t_tuple a2 = {3, -2, 5, VECTOR};
	t_tuple b2 = {-2, 3, 1, VECTOR};
	t_tuple result2;

	result2 = add_tuples(a2, b2);
	UNIT_ASSERT_FEQ(result2.x, 1.0);
	UNIT_ASSERT_FEQ(result2.y, 1.0);
	UNIT_ASSERT_FEQ(result2.z, 6.0);
	UNIT_ASSERT_EQ(result2.type, VECTOR);
	
	t_tuple a3 = {3, -2, 5, POINT};
	t_tuple b3 = {-2, 3, 1, POINT};
	t_tuple result3;

	result3 = add_tuples(a3, b3);
	UNIT_ASSERT_EQ(result3.type, INVALID_POS);

	t_tuple b4 = {3, -2, 5, VECTOR};
	t_tuple a4 = {-2, 3, 1, POINT};
	t_tuple result4;

	result4 = add_tuples(b4, a4);
	UNIT_ASSERT_FEQ(result4.x, 1.0);
	UNIT_ASSERT_FEQ(result4.y, 1.0);
	UNIT_ASSERT_FEQ(result4.z, 6.0);
	UNIT_ASSERT_EQ(result4.type, POINT);

	return (0);
}

int	test_tuple_subtraction(void)
{
	t_tuple c = {3, 2, 1, POINT};
	t_tuple d = {5, 6, 7, POINT};
	t_tuple result;

	result = sub_tuples(c, d);
	UNIT_ASSERT_FEQ(result.x, -2.0);
	UNIT_ASSERT_FEQ(result.y, -4.0);
	UNIT_ASSERT_FEQ(result.z, -6.0);
	UNIT_ASSERT_EQ(result.type, VECTOR);

	t_tuple c2 = {3, 2, 1, POINT};
	t_tuple d2 = {5, 6, 7, VECTOR};
	t_tuple result2;

	result2 = sub_tuples(c2, d2);
	UNIT_ASSERT_FEQ(result2.x, -2.0);
	UNIT_ASSERT_FEQ(result2.y, -4.0);
	UNIT_ASSERT_FEQ(result2.z, -6.0);
	UNIT_ASSERT_EQ(result2.type, POINT);

	t_tuple c3 = {3, 2, 1, VECTOR};
	t_tuple d3 = {5, 6, 7, VECTOR};
	t_tuple result3;

	result3 = sub_tuples(c3, d3);
	UNIT_ASSERT_FEQ(result3.x, -2.0);
	UNIT_ASSERT_FEQ(result3.y, -4.0);
	UNIT_ASSERT_FEQ(result3.z, -6.0);
	UNIT_ASSERT_EQ(result3.type, VECTOR);

	t_tuple c4 = {3, 2, 1, VECTOR};
	t_tuple d4 = {5, 6, 7, POINT};
	t_tuple result4;

	result4 = sub_tuples(c4, d4);
	UNIT_ASSERT_FEQ(result4.x, -2.0);
	UNIT_ASSERT_FEQ(result4.y, -4.0);
	UNIT_ASSERT_FEQ(result4.z, -6.0);
	UNIT_ASSERT_EQ(result4.type, INVALID_NEG);

	t_tuple zero = {0, 0, 0, VECTOR};
	t_tuple	v = {1, -2, 3, VECTOR};
	t_tuple = neg;

	neg = sub_tuples(zero, )
	return (0);
}

