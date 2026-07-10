#include "libunit_assert.h"
#include "minirt.h"
#include <linux/limits.h>
#include <math.h>

int	test_t_tuple_values(void) {
	t_tuple vector;

	vector.x = 1.0;
	vector.y = 0.5;
	vector.z = 2.0;
	vector.w = VECTOR;

	UNIT_ASSERT_FEQ(vector.x, 1.0);
	UNIT_ASSERT_FEQ(vector.y, 0.5);
	UNIT_ASSERT_FEQ(vector.z, 2.0);
	UNIT_ASSERT_FEQ(vector.w, VECTOR);

	t_tuple point;

	point.x = 12.1;
	point.y = 10.3;
	point.z = 0.4;
	point.w = POINT;

	UNIT_ASSERT_FEQ(point.x, 12.1);
	UNIT_ASSERT_FEQ(point.y, 10.3);
	UNIT_ASSERT_FEQ(point.z, 0.4);
	UNIT_ASSERT_FEQ(point.w, POINT);

	return (0);
}

int test_tuple_utils(void) {
	UNIT_ASSERT_EQ(compare_doubles(1.0, 1.0), 0);

	t_tuple a = {1.0, 2.0, 3.0, POINT};
	t_tuple b = {1.0, 2.0, 3.0, POINT};

	UNIT_ASSERT_EQ(compare_tuples(&a, &b), 0);
	return (0);
}

int test_tuple_addition(void) {
	t_tuple a = {3, -2, 5, POINT};
	t_tuple b = {-2, 3, 1, VECTOR};
	t_tuple result;

	result = tuples_add(a, b);
	UNIT_ASSERT_FEQ(result.x, 1.0);
	UNIT_ASSERT_FEQ(result.y, 1.0);
	UNIT_ASSERT_FEQ(result.z, 6.0);
	UNIT_ASSERT_FEQ(result.w, POINT);

	t_tuple a2 = {3, -2, 5, VECTOR};
	t_tuple b2 = {-2, 3, 1, VECTOR};
	t_tuple result2;

	result2 = tuples_add(a2, b2);
	UNIT_ASSERT_FEQ(result2.x, 1.0);
	UNIT_ASSERT_FEQ(result2.y, 1.0);
	UNIT_ASSERT_FEQ(result2.z, 6.0);
	UNIT_ASSERT_FEQ(result2.w, VECTOR);

	t_tuple a3 = {3, -2, 5, POINT};
	t_tuple b3 = {-2, 3, 1, POINT};
	t_tuple result3;

	result3 = tuples_add(a3, b3);
	UNIT_ASSERT_FEQ(result3.w, INVALID_POS);

	t_tuple b4 = {3, -2, 5, VECTOR};
	t_tuple a4 = {-2, 3, 1, POINT};
	t_tuple result4;

	result4 = tuples_add(b4, a4);
	UNIT_ASSERT_FEQ(result4.x, 1.0);
	UNIT_ASSERT_FEQ(result4.y, 1.0);
	UNIT_ASSERT_FEQ(result4.z, 6.0);
	UNIT_ASSERT_FEQ(result4.w, POINT);

	return (0);
}

int test_tuple_subtraction(void) {
	t_tuple c = {3, 2, 1, POINT};
	t_tuple d = {5, 6, 7, POINT};
	t_tuple result;

	result = tuples_sub(c, d);
	UNIT_ASSERT_FEQ(result.x, -2.0);
	UNIT_ASSERT_FEQ(result.y, -4.0);
	UNIT_ASSERT_FEQ(result.z, -6.0);
	UNIT_ASSERT_FEQ(result.w, VECTOR);

	t_tuple c2 = {3, 2, 1, POINT};
	t_tuple d2 = {5, 6, 7, VECTOR};
	t_tuple result2;

	result2 = tuples_sub(c2, d2);
	UNIT_ASSERT_FEQ(result2.x, -2.0);
	UNIT_ASSERT_FEQ(result2.y, -4.0);
	UNIT_ASSERT_FEQ(result2.z, -6.0);
	UNIT_ASSERT_FEQ(result2.w, POINT);

	t_tuple c3 = {3, 2, 1, VECTOR};
	t_tuple d3 = {5, 6, 7, VECTOR};
	t_tuple result3;

	result3 = tuples_sub(c3, d3);
	UNIT_ASSERT_FEQ(result3.x, -2.0);
	UNIT_ASSERT_FEQ(result3.y, -4.0);
	UNIT_ASSERT_FEQ(result3.z, -6.0);
	UNIT_ASSERT_FEQ(result3.w, VECTOR);

	t_tuple c4 = {3, 2, 1, VECTOR};
	t_tuple d4 = {5, 6, 7, POINT};
	t_tuple result4;

	result4 = tuples_sub(c4, d4);
	UNIT_ASSERT_FEQ(result4.x, -2.0);
	UNIT_ASSERT_FEQ(result4.y, -4.0);
	UNIT_ASSERT_FEQ(result4.z, -6.0);
	UNIT_ASSERT_FEQ(result4.w, INVALID_NEG);

	t_tuple zero = {0, 0, 0, VECTOR};
	t_tuple v = {1, -2, 3, VECTOR};
	t_tuple neg;

	neg = tuples_sub(zero, v);
	UNIT_ASSERT_FEQ(neg.x, -1.0);
	UNIT_ASSERT_FEQ(neg.y, 2.0);
	UNIT_ASSERT_FEQ(neg.z, -3.0);
	UNIT_ASSERT_FEQ(neg.w, VECTOR);
	return (0);
}

int	test_tuple_negate(void)
{
	t_tuple	t = {1, -2, 3, -4};
	t_tuple res;

	res = tuple_neg(t);
	UNIT_ASSERT_FEQ(res.x, -1.0);
	UNIT_ASSERT_FEQ(res.y, 2.0);
	UNIT_ASSERT_FEQ(res.z, -3.0);
	UNIT_ASSERT_FEQ(res.w, 4.0);
	return (0);
}

int test_tuple_mul(void)
{
	t_tuple	a = {1, -2, 3, -4};
	t_tuple prod;

	prod = tuple_mult(a, 3.5);
	UNIT_ASSERT_FEQ(prod.x, 3.5);
	UNIT_ASSERT_FEQ(prod.y, -7.0);
	UNIT_ASSERT_FEQ(prod.z, 10.5);
	UNIT_ASSERT_FEQ(prod.w, -14.0);

	t_tuple	b = {1, -2, 3, -4};
	t_tuple prod2;

	prod2 = tuple_mult(b, 0.5);
	UNIT_ASSERT_FEQ(prod2.x, 0.5);
	UNIT_ASSERT_FEQ(prod2.y, -1.0);
	UNIT_ASSERT_FEQ(prod2.z, 1.5);
	UNIT_ASSERT_FEQ(prod2.w, -2.0);
	return (0);
}

int	test_tuple_div(void)
{
	t_tuple	a = {1, -2, 3, 4};
	t_tuple quo;

	quo = tuple_div(a, 2.0);
	UNIT_ASSERT_FEQ(quo.x, 0.5);
	UNIT_ASSERT_FEQ(quo.y, -1.0);
	UNIT_ASSERT_FEQ(quo.z, 1.5);
	UNIT_ASSERT_FEQ(quo.w, 2.0);
	return (0);
}

int	test_tuple_mag(void)
{
	t_tuple	a1 = {1, 0, 0, 0};
	t_tuple	a2 = {0, 1, 0, 0};
	t_tuple	a3 = {0, 0, 1, 0};
	t_tuple	a4 = {1, 2, 3, 0};
	t_tuple	a5 = {-1, -2, -3, 0};

	double m1 = calc_mag(a1);
	double m2 = calc_mag(a2);
	double m3 = calc_mag(a3);
	double m4 = calc_mag(a4);
	double m5 = calc_mag(a5);

	UNIT_ASSERT_FEQ(m1, 1.0);
	UNIT_ASSERT_FEQ(m2, 1.0);
	UNIT_ASSERT_FEQ(m3, 1.0);
	UNIT_ASSERT_FEQ(m4, sqrt(14.0));
	UNIT_ASSERT_FEQ(m5, sqrt(14.0));

	return (0);
}

int	test_tuple_norm(void)
{
	t_tuple a1 = {4, 0, 0, 0};
	t_tuple a2 = {1, 2, 3, 0};

	t_tuple n1 = calc_norm(a1);
	t_tuple n2 = calc_norm(a2);

	UNIT_ASSERT_FEQ(n1.x, 1.0);
	UNIT_ASSERT_FEQ(n1.y, 0);
	UNIT_ASSERT_FEQ(n1.z, 0);
	UNIT_ASSERT_FEQ(n1.w, 0);

	UNIT_ASSERT_FEQ(n2.x, 1 / sqrt(14));
	UNIT_ASSERT_FEQ(n2.y, 2 / sqrt(14));
	UNIT_ASSERT_FEQ(n2.z, 3 / sqrt(14));
	UNIT_ASSERT_FEQ(n2.w, 0 / sqrt(14));

	t_tuple a3 = {1, 2, 3, 0};
	t_tuple norm = calc_norm(a3);
	double mag = calc_mag(norm);
	UNIT_ASSERT_FEQ(mag, 1.0);

	return (0);
}

int	test_tuple_dot(void)
{
	t_tuple a = {1, 2, 3, 0};
	t_tuple b = {2, 3, 4, 0};

	double d = dot_product(a, b);
	UNIT_ASSERT_FEQ(d, 20.0);

	return (0);
}

int	test_tuple_cross(void)
{
	t_tuple a = {1, 2, 3, 0};
	t_tuple b = {2, 3, 4, 0};

	t_tuple ab = cross_product(a, b);
	t_tuple ba = cross_product(b, a);

	t_tuple c1 = {-1, 2, -1, 0};
	t_tuple c2 = {1, -2, 1, 0};

	UNIT_ASSERT_EQ(compare_tuples(&ab, &c1), 0);
	UNIT_ASSERT_EQ(compare_tuples(&ba, &c2), 0);
	return (0);
}