/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:43:19 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 18:27:52 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libunit_assert.h"
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"
#include "util/cylinders.h"
#include "util/intersections.h"
#include "util/planes.h"
#include "util/spheres.h"

int	test_default_scene(void)
{
	t_scene	scene1;

	if (!init_scene(&scene1))
		return (1);

	UNIT_ASSERT_EQ(spheres_len(scene1.spheres), 0);
	UNIT_ASSERT_EQ(planes_len(scene1.planes), 0);
	UNIT_ASSERT_EQ(cylinders_len(scene1.cylinders), 0);

	t_scene	scene2;

	if (!default_scene(&scene2))
		return (1);

	t_color	expected;

	expected = color(0.8, 1.0, 0.6);

	UNIT_ASSERT_EQ(spheres_len(scene2.spheres), 2);
	UNIT_ASSERT_EQ(compare_tuples(&scene2.spheres[0]->material.color, &expected), 0);
	UNIT_ASSERT_FEQ(scene2.spheres[0]->material.diffuse, 0.7);
	UNIT_ASSERT_FEQ(scene2.spheres[0]->material.specular, 0.2);
	UNIT_ASSERT_EQ(matrix4x4_compare(scene2.spheres[1]->transform, matrix4x4_scaling(0.5, 0.5, 0.5)), 0);
	UNIT_ASSERT_EQ(planes_len(scene2.planes), 0);
	UNIT_ASSERT_EQ(cylinders_len(scene2.cylinders), 0);

	return (0);
}

int	test_intersect_scene(void)
{
	t_scene			scene;
	t_ray			ray;
	t_intersection	**intersections;

	if (!default_scene(&scene))
		return (1);
	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
	intersections = intersect_scene(&scene, ray);

	UNIT_ASSERT_EQ(intersections_len(intersections), 4);
	UNIT_ASSERT_FEQ(intersections[0]->t, 4);
	UNIT_ASSERT_FEQ(intersections[1]->t, 4.5);
	UNIT_ASSERT_FEQ(intersections[2]->t, 5.5);
	UNIT_ASSERT_FEQ(intersections[3]->t, 6.0);

	return (0);
}

int	test_prepare_computations(void)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersection	*hit;
	t_comps			comps;

	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
	sphere = sphere_create();
	hit = create_intersection(SPHERE, &sphere, 4.0);
	comps = prepare_computations(ray, hit);

	t_point			p;
	t_vector		eyev;
	t_vector		normalv;

	p = point(0.0, 0.0, -1.0);
	eyev = vector(0.0, 0.0, -1.0);
	normalv = vector(0.0, 0.0, -1.0);

	UNIT_ASSERT_FEQ(comps.t, hit->t);
	UNIT_ASSERT_EQ(comps.obj.object, hit->obj.object);
	UNIT_ASSERT_EQ(compare_tuples(&comps.point, &p), 0);
	UNIT_ASSERT_EQ(compare_tuples(&comps.eyev, &eyev), 0);
	UNIT_ASSERT_EQ(compare_tuples(&comps.normalv, &normalv), 0);
	free(hit);

	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
	sphere = sphere_create();
	hit = create_intersection(SPHERE, &sphere, 4.0);
	comps = prepare_computations(ray, hit);

	UNIT_ASSERT_EQ(comps.inside, 0);
	free(hit);

	ray = (t_ray){point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0)};
	sphere = sphere_create();
	hit = create_intersection(SPHERE, &sphere, 1.0);
	comps = prepare_computations(ray, hit);

	p = point(0.0, 0.0, 1.0);
	eyev = vector(0.0, 0.0, -1.0);
	normalv = vector(0.0, 0.0, -1.0);

	UNIT_ASSERT_EQ(compare_tuples(&comps.point, &p), 0);
	UNIT_ASSERT_EQ(compare_tuples(&comps.eyev, &eyev), 0);
	UNIT_ASSERT_EQ(compare_tuples(&comps.normalv, &normalv), 0);
	UNIT_ASSERT_EQ(comps.inside, 1);

	return (0);
}

int	test_shade_hit(void)
{
	t_scene			scene;
	t_ray			ray;
	t_sphere		*sphere;
	t_intersection	*hit;
	t_comps			comps;
	t_color			c;

	t_color			expected;

	if (!default_scene(&scene))
		return (1);
	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
	sphere = scene.spheres[0];
	hit = create_intersection(SPHERE, sphere, 4.0);
	comps = prepare_computations(ray, hit);
	c = shade_hit(&scene, comps);

	expected = color(0.38066, 0.47583, 0.2855);

	UNIT_ASSERT_EQ(compare_tuples(&c, &expected), 0);
	destroy_scene(&scene);
	free(hit);

	if (!default_scene(&scene))
		return (1);
	scene.light = (t_light){point(0.0, 0.25, 0.0), color(1.0, 1.0, 1.0)};
	ray = (t_ray){point(0.0, 0.0, 0.0), vector(0.0, 0.0, 1.0)};
	sphere = scene.spheres[1];
	hit = create_intersection(SPHERE, sphere, 0.5);
	comps = prepare_computations(ray, hit);
	c = shade_hit(&scene, comps);

	expected = color(0.90498, 0.90498, 0.90498);

	UNIT_ASSERT_EQ(compare_tuples(&c, &expected), 0);
	destroy_scene(&scene);
	free(hit);

	return (0);
}
