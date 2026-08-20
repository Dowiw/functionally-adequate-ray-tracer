/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rendering.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 15:43:19 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "graphics.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"
#include "util/cylinders.h"
#include "util/intersections.h"
#include "util/planes.h"
#include "util/spheres.h"

static int	default_scene(t_scene *scene)
{
	t_sphere	*sphere;

	init_scene(scene);
	scene->light = (t_light){point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0)};
	sphere = malloc(sizeof(t_sphere));
	if (sphere != NULL)
	{
		*sphere = sphere_create();
		sphere->material.color = color(0.8, 1.0, 0.6);
		sphere->material.diffuse = 0.7;
		sphere->material.specular = 0.2;
	}
	scene->spheres = spheres_add(scene->spheres, sphere);
	sphere = malloc(sizeof(t_sphere));
	if (sphere != NULL)
	{
		*sphere = sphere_create();
		sphere->transform = m4x4_scaling(0.5, 0.5, 0.5);
		sphere->inverse = m4x4_inverse(sphere->transform);
	}
	scene->spheres = spheres_add(scene->spheres, sphere);
	if (scene->spheres == NULL)
	{
		destroy_scene(scene);
		return (0);
	}
	return (1);
}

int	test_intersect_scene(void)
{
	t_scene			scene;
	t_ray			ray;
	t_intersects	intersections;

	if (!default_scene(&scene))
		return (1);
	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};
	intersections = intersect_scene(&scene, ray);

	UNIT_ASSERT_EQ(intersections.count, 4);
	UNIT_ASSERT_FEQ(intersections.list[0]->t, 4);
	UNIT_ASSERT_FEQ(intersections.list[1]->t, 4.5);
	UNIT_ASSERT_FEQ(intersections.list[2]->t, 5.5);
	UNIT_ASSERT_FEQ(intersections.list[3]->t, 6.0);

	free_intersections(intersections);
	destroy_scene(&scene);
	return (0);
}

int	test_prepare_computations(void)
{
	t_ray			ray;
	t_sphere		sphere;
	t_intersect	*hit;
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
	UNIT_ASSERT_EQ(comps.obj.ptr, hit->obj.ptr);
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
	t_intersect	*hit;
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

int	test_color_at(void)
{
	t_scene		scene1;
	t_ray		ray;
	t_color		c;

	if (!default_scene(&scene1))
		return (1);
	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 1.0, 0.0)};

	c = color_at(&scene1, ray);

	t_color		expected;

	expected = color(0.0, 0.0, 0.0);

	UNIT_ASSERT_EQ(compare_tuples(&c, &expected), 0);
	destroy_scene(&scene1);

	t_scene		scene2;

	if (!default_scene(&scene2))
		return (1);
	ray = (t_ray){point(0.0, 0.0, -5.0), vector(0.0, 0.0, 1.0)};

	c = color_at(&scene2, ray);

	expected = color(0.38066, 0.47583, 0.2855);

	UNIT_ASSERT_EQ(compare_tuples(&c, &expected), 0);
	destroy_scene(&scene2);

	t_scene		scene3;
	t_sphere	*outer;
	t_sphere	*inner;

	if (!default_scene(&scene3))
		return (1);
	outer = scene3.spheres[0];
	outer->material.ambient = 1.0;
	inner = scene3.spheres[1];
	inner->material.ambient = 1.0;
	ray = (t_ray){point(0.0, 0.0, 0.75), vector(0.0, 0.0, -1.0)};

	c = color_at(&scene3, ray);

	UNIT_ASSERT_EQ(compare_tuples(&c, &inner->material.color), 0);
	destroy_scene(&scene3);

	return (0);
}

int	test_view_transform(void)
{
	t_point	from;
	t_point	to;
	t_point	up;

	from = point(0.0, 0.0, 0.0);
	to = point(0.0, 0.0, -1.0);
	up = vector(0.0, 1.0, 0.0);

	UNIT_ASSERT_EQ(m4x4_compare(view_transform(from, to, up), m4x4_identity()), 0);

	from = point(0.0, 0.0, 0.0);
	to = point(0.0, 0.0, 1.0);
	up = vector(0.0, 1.0, 0.0);

	UNIT_ASSERT_EQ(m4x4_compare(view_transform(from, to, up), m4x4_scaling(-1.0, 1.0, -1.0)), 0);

	from = point(0.0, 0.0, 8.0);
	to = point(0.0, 0.0, 0.0);
	up = vector(0.0, 1.0, 0.0);

	UNIT_ASSERT_EQ(m4x4_compare(view_transform(from, to, up), m4x4_translation(0.0, 0.0, -8.0)), 0);

	from = point(1.0, 3.0, 2.0);
	to = point(4.0, -2.0, 8.0);
	up = vector(1.0, 1.0, 0.0);

	t_m4x4	expected;

	expected = (t_m4x4){{
		{-0.50709, 0.50709, 0.67612, -2.36643},
		{0.76772, 0.60609, 0.12122, -2.82843},
		{-0.35857, 0.59761, -0.71714, 0.00000},
		{0.00000, 0.00000, 0.00000, 1.00000}
	}};

	UNIT_ASSERT_EQ(m4x4_compare(view_transform(from, to, up), expected), 0);

	return (0);
}

int	test_camera(void)
{
	t_camera	camera;

	camera = create_camera(160, 120, PI / 2.0);

	UNIT_ASSERT_EQ(camera.width, 160);
	UNIT_ASSERT_EQ(camera.height, 120);
	UNIT_ASSERT_FEQ(camera.field_of_view, PI / 2.0);
	UNIT_ASSERT_EQ(m4x4_compare(camera.transform, m4x4_identity()), 0);

	camera = create_camera(200, 125, PI / 2.0);

	UNIT_ASSERT_FEQ(camera.pixel_size, 0.01);

	return (0);
}

int	test_ray_for_pixel(void)
{
	t_camera	camera;
	t_ray		ray;

	camera = create_camera(201, 101, PI / 2.0);
	ray = ray_for_pixel(camera, 100, 50);

	t_point		origin;
	t_vector	direction;

	origin = point(0.0, 0.0, 0.0);
	direction = vector(0.0, 0.0, -1.0);

	UNIT_ASSERT_EQ(compare_tuples(&ray.origin, &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&ray.dir, &direction), 0);

	camera = create_camera(201, 101, PI / 2.0);
	ray = ray_for_pixel(camera, 0, 0);

	origin = point(0.0, 0.0, 0.0);
	direction = vector(0.66519, 0.33259, -0.66851);

	UNIT_ASSERT_EQ(compare_tuples(&ray.origin, &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&ray.dir, &direction), 0);

	camera = create_camera(201, 101, PI / 2.0);
	camera.transform = m4x4_multiply(m4x4_rotation_y(PI / 4.0), m4x4_translation(0.0, -2.0, 5.0));
	camera.inverse = m4x4_inverse(camera.transform);
	ray = ray_for_pixel(camera, 100, 50);

	origin = point(0.0, 2.0, -5.0);
	direction = vector(sqrt(2.0) / 2.0, 0.0, -sqrt(2.0) / 2.0);

	UNIT_ASSERT_EQ(compare_tuples(&ray.origin, &origin), 0);
	UNIT_ASSERT_EQ(compare_tuples(&ray.dir, &direction), 0);

	return (0);
}

int	test_render_scene(void)
{
	t_scene		scene;
	t_point		from;
	t_point		to;
	t_vector	up;
	t_canvas	canvas;

	if (!default_scene(&scene))
		return (1);
	scene.camera = create_camera(11, 11, PI / 2.0);
	from = point(0.0, 0.0, -5.0);
	to = point(0.0, 0.0, 0.0);
	up = vector(0.0, 1.0, 0.0);
	scene.camera.transform = view_transform(from, to, up);
	scene.camera.inverse = m4x4_inverse(scene.camera.transform);
	if (!canvas_create(&canvas, scene.camera.width, scene.camera.height))
		return (1);

	render_scene(&canvas, &scene);

	t_color		pixel;
	t_color		expected;

	pixel = view_pixel(&canvas, 5, 5);
	expected = color(0.38066, 0.47583, 0.2855);

	UNIT_ASSERT_EQ(compare_tuples(&pixel, &expected), 0);

	return (0);
}
