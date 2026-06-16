#include "libunit_assert.h"
#include "minirt.h"

int	test_matrix_values(void)
{
	t_matrix2x2	m2;

	m2 = (t_matrix2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};

	UNIT_ASSERT_FEQ(m2.m[0][0], 1.0);
	UNIT_ASSERT_FEQ(m2.m[0][1], 2.0);
	UNIT_ASSERT_FEQ(m2.m[1][0], 3.0);
	UNIT_ASSERT_FEQ(m2.m[1][1], 4.0);

	t_matrix3x3	m3;

	m3 = (t_matrix3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, -54.321, 0.0},
		{7.2, 89.99, 7.2}
	}};

	UNIT_ASSERT_FEQ(m3.m[0][0], -3.2);
	UNIT_ASSERT_FEQ(m3.m[0][1], 0.0);
	UNIT_ASSERT_FEQ(m3.m[0][2], 56.0);
	UNIT_ASSERT_FEQ(m3.m[1][0], 1111.11);
	UNIT_ASSERT_FEQ(m3.m[1][1], -54.321);
	UNIT_ASSERT_FEQ(m3.m[1][2], 0.0);
	UNIT_ASSERT_FEQ(m3.m[2][0], 7.2);
	UNIT_ASSERT_FEQ(m3.m[2][1], 89.99);
	UNIT_ASSERT_FEQ(m3.m[2][2], 7.2);

	t_matrix4x4	m4;

	m4 = (t_matrix4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{0.0, 1.0, 2.0, 3.0},
		{9999.99, 999.999, 99.9999, 9.99999},
		{-7.2, 7.2, -7.2, 72}
	}};

	UNIT_ASSERT_FEQ(m4.m[0][0], -12.12);
	UNIT_ASSERT_FEQ(m4.m[0][1], 11.11);
	UNIT_ASSERT_FEQ(m4.m[0][2], -10.1);
	UNIT_ASSERT_FEQ(m4.m[0][3], 9.9);
	UNIT_ASSERT_FEQ(m4.m[1][0], 0.0);
	UNIT_ASSERT_FEQ(m4.m[1][3], 3.0);
	UNIT_ASSERT_FEQ(m4.m[2][2], 99.9999);
	UNIT_ASSERT_FEQ(m4.m[3][1], 7.2);

	return (0);
}

int	test_matrix_compare(void)
{
	t_matrix2x2	m2a;
	t_matrix2x2	m2b;
	t_matrix2x2	m2c;

	m2a = (t_matrix2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};
	m2b = (t_matrix2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};
	m2c = (t_matrix2x2){{
		{1.0, -2.0},
		{3.0, 4.0}
	}};

	UNIT_ASSERT_EQ(matrix2x2_compare(m2a, m2a), 0);
	UNIT_ASSERT_EQ(matrix2x2_compare(m2a, m2b), 0);
	UNIT_ASSERT_EQ(matrix2x2_compare(m2a, m2c), 1);

	t_matrix3x3	m3a;
	t_matrix3x3	m3b;
	t_matrix3x3	m3c;

	m3a = (t_matrix3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, -54.321, 0.0},
		{7.2, 89.99, 7.2}
	}};
	m3b = (t_matrix3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, -54.321, 0.0},
		{7.2, 89.99, 7.2}
	}};
	m3c = (t_matrix3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, 987654.321, 0.0},
		{7.2, 89.99, 7.2}
	}};

	UNIT_ASSERT_EQ(matrix3x3_compare(m3a, m3a), 0);
	UNIT_ASSERT_EQ(matrix3x3_compare(m3a, m3b), 0);
	UNIT_ASSERT_EQ(matrix3x3_compare(m3a, m3c), 1);

	t_matrix4x4	m4a;
	t_matrix4x4	m4b;
	t_matrix4x4	m4c;

	m4a = (t_matrix4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{0.0, 1.0, 2.0, 3.0},
		{9999.99, 999.999, 99.9999, 9.99999},
		{-7.2, 7.2, -7.2, 72}
	}};
	m4b = (t_matrix4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{0.0, 1.0, 2.0, 3.0},
		{9999.99, 999.999, 99.9999, 9.99999},
		{-7.2, 7.2, -7.2, 72}
	}};
	m4c = (t_matrix4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{9999.99, 999.999, 99.9999, 9.99999},
		{0.0, 1.0, 2.0, 3.0},
		{-7.2, 7.2, -7.2, 72}
	}};

	UNIT_ASSERT_EQ(matrix4x4_compare(m4a, m4a), 0);
	UNIT_ASSERT_EQ(matrix4x4_compare(m4a, m4b), 0);
	UNIT_ASSERT_EQ(matrix4x4_compare(m4a, m4c), 1);

	return (0);
}
