/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cones.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:30:00 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/17 18:54:38 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libunit.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "ray.h"
#include "scene.h"
#include "util/cones.h"
#include <math.h>

int	test_cones_intersections(void)
{
	t_cone			c = cone_create();
	t_point			o[3] = {
		{0, 0, -5, POINT},
		{0, 0, -5, POINT},
		{1, 1, -5, POINT}
	};
	t_vector		d[3] = {
		{0, 0, 1, VECTOR},
		{1, 1, 1, VECTOR},
		{-0.5, -1, 1, VECTOR}
	};
	double			t0[3] = {5.0, 8.66025, 4.55006};
	double			t1[3] = {5.0, 8.66025, 49.44994};
	t_vector		direction;
	t_ray			r;
	t_intersections	xs;
	t_object		obj = (t_object){CONE, &c};

	for (int i = 0; i < 3; i++)
	{
		direction = calc_norm(d[i]);
		r = ray(o[i], direction);
		xs = intersect(&obj, r);
		UNIT_ASSERT_EQ(xs.count, 2);
		UNIT_ASSERT_FEQ(xs.list[0]->t, t0[i]);
		UNIT_ASSERT_FEQ(xs.list[1]->t, t1[i]);
	}
	return (0);
}

int	test_cones_parallel_intersection(void)
{
	t_cone			c = cone_create();
	t_vector		direction = calc_norm(vector(0, 1, 1));
	t_ray			r = ray(point(0, 0, -1), direction);
	t_object		obj = (t_object){CONE, &c};
	t_intersections	xs = intersect(&obj, r);

	UNIT_ASSERT_EQ(xs.count, 1);
	UNIT_ASSERT_FEQ(xs.list[0]->t, 0.70710);
	return (0);
}

int	test_cones_end_caps(void)
{
	t_cone			c = cone_create();
	c.min = -0.5;
	c.max = 0.5;
	c.closed = 1;

	t_point			o[3] = {
		{0, 0, -5, POINT},
		{0, 0, -0.25, POINT},
		{0, 0, -0.25, POINT}
	};
	t_vector		d[3] = {
		{0, 1, 0, VECTOR},
		{0, 1, 1, VECTOR},
		{0, 1, 0, VECTOR}
	};
	int				counts[3] = {0, 2, 4};
	t_vector		direction;
	t_ray			r;
	t_intersections	xs;
	t_object		obj = (t_object){CONE, &c};

	for (int i = 0; i < 3; i++)
	{
		direction = calc_norm(d[i]);
		r = ray(o[i], direction);
		xs = intersect(&obj, r);
		UNIT_ASSERT_EQ(xs.count, counts[i]);
	}
	return (0);
}

int	test_cones_normal(void)
{
	t_cone		c = cone_create();
	t_point		p[3] = {
		{0, 0, 0, POINT},
		{1, 1, 1, POINT},
		{-1, -1, 0, POINT}
	};
	t_vector	expected_normal[3] = {
		{0, 0, 0, VECTOR},
		{1, -sqrt(2.0), 1, VECTOR},
		{-1, 1, 0, VECTOR}
	};
	t_object	obj = (t_object){CONE, &c};
	t_vector	res;
	t_vector	norm_exp;

	for (int i = 0; i < 3; i++)
	{
		res = normal_at(&obj, p[i]);
		if (calc_mag(expected_normal[i]) > 0)
			norm_exp = calc_norm(expected_normal[i]);
		else
			norm_exp = expected_normal[i];
		UNIT_ASSERT_EQ(compare_tuples(&res, &norm_exp), 0);
	}
	return (0);
}
