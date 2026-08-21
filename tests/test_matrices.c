#include "libunit_assert.h"
#include "minirt.h"

int	test_matrix_values(void)
{
	t_m2x2	m2;

	m2 = (t_m2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};

	UNIT_ASSERT_FEQ(m2.m[0][0], 1.0);
	UNIT_ASSERT_FEQ(m2.m[0][1], 2.0);
	UNIT_ASSERT_FEQ(m2.m[1][0], 3.0);
	UNIT_ASSERT_FEQ(m2.m[1][1], 4.0);

	t_m3x3	m3;

	m3 = (t_m3x3){{
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

	t_m4x4	m4;

	m4 = (t_m4x4){{
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

int	test_matrix_identity(void)
{
	t_m2x2	m2;

	m2 = m2x2_identity();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			if (i == j)
			{
				UNIT_ASSERT_EQ(m2.m[i][j], 1.0);
			}
			else
			{
				UNIT_ASSERT_EQ(m2.m[i][j], 0.0);
			}
		}
	}

	t_m3x3	m3;

	m3 = m3x3_identity();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == j)
			{
				UNIT_ASSERT_EQ(m3.m[i][j], 1.0);
			}
			else
			{
				UNIT_ASSERT_EQ(m3.m[i][j], 0.0);
			}
		}
	}

	t_m4x4	m4;

	m4 = m4x4_identity();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
			{
				UNIT_ASSERT_EQ(m4.m[i][j], 1.0);
			}
			else
			{
				UNIT_ASSERT_EQ(m4.m[i][j], 0.0);
			}
		}
	}

	return (0);
}

int	test_matrix_compare(void)
{
	t_m2x2	m2a;
	t_m2x2	m2b;
	t_m2x2	m2c;

	m2a = (t_m2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};
	m2b = (t_m2x2){{
		{1.0, 2.0},
		{3.0, 4.0}
	}};
	m2c = (t_m2x2){{
		{1.0, -2.0},
		{3.0, 4.0}
	}};

	UNIT_ASSERT_EQ(m2x2_compare(m2a, m2a), 0);
	UNIT_ASSERT_EQ(m2x2_compare(m2a, m2b), 0);
	UNIT_ASSERT_EQ(m2x2_compare(m2a, m2c), 1);

	t_m3x3	m3a;
	t_m3x3	m3b;
	t_m3x3	m3c;

	m3a = (t_m3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, -54.321, 0.0},
		{7.2, 89.99, 7.2}
	}};
	m3b = (t_m3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, -54.321, 0.0},
		{7.2, 89.99, 7.2}
	}};
	m3c = (t_m3x3){{
		{-3.2, 0.0, 56.0},
		{1111.11, 987654.321, 0.0},
		{7.2, 89.99, 7.2}
	}};

	UNIT_ASSERT_EQ(m3x3_compare(m3a, m3a), 0);
	UNIT_ASSERT_EQ(m3x3_compare(m3a, m3b), 0);
	UNIT_ASSERT_EQ(m3x3_compare(m3a, m3c), 1);

	t_m4x4	m4a;
	t_m4x4	m4b;
	t_m4x4	m4c;

	m4a = (t_m4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{0.0, 1.0, 2.0, 3.0},
		{9999.99, 999.999, 99.9999, 9.99999},
		{-7.2, 7.2, -7.2, 72}
	}};
	m4b = (t_m4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{0.0, 1.0, 2.0, 3.0},
		{9999.99, 999.999, 99.9999, 9.99999},
		{-7.2, 7.2, -7.2, 72}
	}};
	m4c = (t_m4x4){{
		{-12.12, 11.11, -10.1, 9.9},
		{9999.99, 999.999, 99.9999, 9.99999},
		{0.0, 1.0, 2.0, 3.0},
		{-7.2, 7.2, -7.2, 72}
	}};

	UNIT_ASSERT_EQ(m4x4_compare(m4a, m4a), 0);
	UNIT_ASSERT_EQ(m4x4_compare(m4a, m4b), 0);
	UNIT_ASSERT_EQ(m4x4_compare(m4a, m4c), 1);

	return (0);
}

int	test_matrix_multiply(void)
{
	t_m4x4	m4a;
	t_m4x4	m4b;
	t_m4x4	m4expected;
	t_m4x4	m4result;

	m4a = (t_m4x4){{
		{1.0, 2.0, 3.0, 4.0},
		{5.0, 6.0, 7.0, 8.0},
		{9.0, 8.0, 7.0, 6.0},
		{5.0, 4.0, 3.0, 2.0}
	}};
	m4b = (t_m4x4){{
		{-2.0, 1.0, 2.0, 3.0},
		{3.0, 2.0, 1.0, -1.0},
		{4.0, 3.0, 6.0, 5.0},
		{1.0, 2.0, 7.0, 8.0}
	}};
	m4expected = (t_m4x4){{
		{20.0, 22.0, 50.0, 48.0},
		{44.0, 54.0, 114.0, 108.0},
		{40.0, 58.0, 110.0, 102.0},
		{16.0, 26.0, 46.0, 42.0}
	}};

	m4result = m4x4_multiply(m4a, m4b);

	UNIT_ASSERT_EQ(m4x4_compare(m4expected, m4result), 0);

	m4result = m4x4_multiply(m4a, m4x4_identity());

	UNIT_ASSERT_EQ(m4x4_compare(m4a, m4result), 0);

	return (0);
}

int	test_matrix_multiply_tuple(void)
{
	t_m4x4	m4;
	t_tuple		tuple;
	t_tuple		expected;
	t_tuple		result;

	m4 = (t_m4x4){{
		{1.0, 2.0, 3.0, 4.0},
		{2.0, 4.0, 4.0, 2.0},
		{8.0, 6.0, 4.0, 1.0},
		{0.0, 0.0, 0.0, 1.0}
	}};
	tuple = (t_tuple){
		1.0, 2.0, 3.0, 1.0
	};
	expected = (t_tuple){
		18.0, 24.0, 33.0, 1.0
	};

	result = m4x4_multiply_tuple(m4, tuple);

	UNIT_ASSERT_EQ(compare_tuples(&expected, &result), 0);

	return (0);
}

int	test_matrix_transpose(void)
{
	t_m2x2	m2;
	t_m2x2	m2result;

	m2 = (t_m2x2){{
		{0.0, 9.0},
		{8.0, 9.0}
	}};

	m2result = m2x2_transpose(m2);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			UNIT_ASSERT_EQ(m2.m[i][j], m2result.m[j][i]);
		}
	}

	t_m3x3	m3;
	t_m3x3	m3result;

	m3 = (t_m3x3){{
		{0.0, 9.0, 3.0},
		{9.0, 8.0, 0.0},
		{1.0, 8.0, 5.0}
	}};

	m3result = m3x3_transpose(m3);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			UNIT_ASSERT_EQ(m3.m[i][j], m3result.m[j][i]);
		}
	}

	t_m4x4	m4;
	t_m4x4	m4result;

	m4 = (t_m4x4){{
		{0.0, 9.0, 3.0, 0.0},
		{9.0, 8.0, 0.0, 8.0},
		{1.0, 8.0, 5.0, 3.0},
		{0.0, 0.0, 5.0, 8.0}
	}};

	m4result = m4x4_transpose(m4);

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			UNIT_ASSERT_EQ(m4.m[i][j], m4result.m[j][i]);
		}
	}

	return (0);
}

int	test_matrix_determinant(void)
{
	double		determinant;

	t_m2x2	m2;

	m2 = (t_m2x2){{
		{1.0, 5.0},
		{-3.0, 2.0}
	}};

	determinant = m2x2_determinant(m2);

	UNIT_ASSERT_FEQ(determinant, 17.0);

	t_m3x3	m3;

	m3 = (t_m3x3){{
		{1.0, 2.0, 6.0},
		{-5.0, 8.0, -4.0},
		{2.0, 6.0, 4.0}
	}};

	determinant = m3x3_determinant(m3);

	UNIT_ASSERT_FEQ(determinant, -196.0);

	t_m4x4	m4;

	m4 = (t_m4x4){{
		{-2.0, -8.0, 3.0, 5.0},
		{-3.0, 1.0, 7.0, 3.0},
		{1.0, 2.0, -9.0, 6.0},
		{-6.0, 7.0, 7.0, -9.0}
	}};

	determinant = m4x4_determinant(m4);

	UNIT_ASSERT_FEQ(determinant, -4071.0);

	return (0);
}

int	test_matrix_submatrix(void)
{
	t_m3x3	m3;
	t_m2x2	m2expected;
	t_m2x2	m2result;

	m3 = (t_m3x3){{
		{1.0, 5.0, 0.0},
		{-3.0, 2.0, 7.0},
		{0.0, 6.0, -3.0}
	}};
	m2expected = (t_m2x2){{
		{-3.0, 2.0},
		{0.0, 6.0}
	}};

	m2result = m3x3_submatrix(m3, 0, 2);

	UNIT_ASSERT_EQ(m2x2_compare(m2expected, m2result), 0);

	t_m4x4	m4;
	t_m3x3	m3expected;
	t_m3x3	m3result;

	m4 = (t_m4x4){{
		{-6.0, 1.0, 1.0, 6.0},
		{-8.0, 5.0, 8.0, 6.0},
		{-1.0, 0.0, 8.0, 2.0},
		{-7.0, 1.0, -1.0, 1.0}
	}};
	m3expected = (t_m3x3){{
		{-6.0, 1.0, 6.0},
		{-8.0, 8.0, 6.0},
		{-7.0, -1.0, 1.0}
	}};

	m3result = m4x4_submatrix(m4, 2, 1);

	UNIT_ASSERT_EQ(m3x3_compare(m3expected, m3result), 0);

	return (0);
}

int	test_matrix_minor(void)
{
	double	minor;
	double	determinant;

	t_m3x3	m3;

	m3 = (t_m3x3){{
		{3.0, 5.0, 0.0},
		{2.0, -1.0, -7.0},
		{6.0, -1.0, 5.0}
	}};

	determinant = m2x2_determinant(m3x3_submatrix(m3, 1, 0));
	minor = m3x3_minor(m3, 1, 0);

	UNIT_ASSERT_FEQ(minor, determinant);
	UNIT_ASSERT_FEQ(minor, 25.0);

	t_m4x4	m4;

	m4 = (t_m4x4){{
		{-2.0, -8.0, 3.0, 5.0},
		{-3.0, 1.0, 7.0, 3.0},
		{1.0, 2.0, -9.0, 6.0},
		{-6.0, 7.0, 7.0, -9.0}
	}};

	determinant = m3x3_determinant(m4x4_submatrix(m4, 0, 1));
	minor = m4x4_minor(m4, 0, 1);

	UNIT_ASSERT_FEQ(minor, determinant);
	UNIT_ASSERT_FEQ(minor, -447.0);

	return (0);
}

int	test_matrix_cofactor(void)
{
	double	minor;
	double	cofactor;

	t_m3x3	m3;

	m3 = (t_m3x3){{
		{3.0, 5.0, 0.0},
		{2.0, -1.0, -7.0},
		{6.0, -1.0, 5.0}
	}};

	minor = m3x3_minor(m3, 0, 0);
	cofactor = m3x3_cofactor(m3, 0, 0);

	UNIT_ASSERT_FEQ(minor, -12.0);
	UNIT_ASSERT_FEQ(cofactor, -12.0);

	minor = m3x3_minor(m3, 1, 0);
	cofactor = m3x3_cofactor(m3, 1, 0);

	UNIT_ASSERT_FEQ(minor, 25.0);
	UNIT_ASSERT_FEQ(cofactor, -25.0);

	t_m4x4	m4;

	m4 = (t_m4x4){{
		{-2.0, -8.0, 3.0, 5.0},
		{-3.0, 1.0, 7.0, 3.0},
		{1.0, 2.0, -9.0, 6.0},
		{-6.0, 7.0, 7.0, -9.0}
	}};

	minor = m4x4_minor(m4, 0, 1);
	cofactor = m4x4_cofactor(m4, 0, 1);

	UNIT_ASSERT_FEQ(minor, -447.0);
	UNIT_ASSERT_FEQ(cofactor, 447.0);

	return (0);
}

int	test_matrix_inverse(void)
{
	t_m4x4	m4;
	t_m4x4	m4expected;
	t_m4x4	m4result;

	m4 = (t_m4x4){{
		{-5.0, 2.0, 6.0, -8.0},
		{1.0, -5.0, 1.0, 8.0},
		{7.0, 7.0, -6.0, -7.0},
		{1.0, -3.0, 7.0, 4.0}
	}};
	m4expected = (t_m4x4){{
		{0.21805, 0.45113, 0.24060, -0.04511},
		{-0.80827, -1.45677, -0.44361, 0.52068},
		{-0.07895, -0.22368, -0.05263, 0.19737},
		{-0.52256, -0.81391, -0.30075, 0.30639}
	}};

	m4result = m4x4_inverse(m4);

	UNIT_ASSERT_EQ(m4x4_compare(m4expected, m4result), 0);

	return (0);
}
