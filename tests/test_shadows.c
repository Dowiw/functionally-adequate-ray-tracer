#include "libunit.h"
#include "libunit_assert.h"
#include "minirt.h"
#include "rendering.h"
#include "scene.h"
#include "util/colors.h"
#include "util/spheres.h"
#include "ray.h"
#include <stdlib.h>

int test_shadow_surface(void)
{
	t_vector eye_v = vector(0, 0, -1);
	t_vector normal_v = vector(0, 0, -1);
	t_light light_p = light(point(0, 0, -10), color(1, 1, 1));
	t_material m = material();
	t_point	p = point(0, 0, 0);
	t_scene	scene;
	t_comps	comps;

	t_ambience	def = {1.0, rgb(255, 255, 255)};

	init_scene(&scene);
	scene.light = light_p;
	scene.ambience = def;
	comps.point = p;
	comps.eyev = eye_v;
	comps.normalv = normal_v;

	t_color	test = lighting(m, scene, comps, 1);

	t_color	b = color(0.1, 0.1, 0.1);
	UNIT_ASSERT_EQ(compare_tuples(&test, &b), 0);
	return (0);
}

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

int	test_shadow_is_shadowed(void)
{
	t_scene	w;

	if (!default_scene(&w))
		return (1);

	t_point	p = point(0, 10, 0);
	UNIT_ASSERT_EQ(is_shadowed(w, p), 0);

	t_point	p2 = point(10, -10, 10);
	UNIT_ASSERT_EQ(is_shadowed(w, p2), 1);

	t_point	p3 = point(-20, 20, -20);
	UNIT_ASSERT_EQ(is_shadowed(w, p3), 0);

	t_point	p4 = point(-2, -2, -2);
	UNIT_ASSERT_EQ(is_shadowed(w, p4), 0);

	return (0);
}

int	test_shadow_shade(void)
{
	t_scene		w;
	t_sphere	*s1;
	t_sphere	*s2;

	if (!init_scene(&w))
		return (1);

	w.light = light(point(0, 0, -10), color(1, 1, 1));

	s1 = malloc(sizeof(t_sphere));
	if (!s1)
		return (1);
	*s1 = sphere_create();
	w.spheres = spheres_add(w.spheres, s1);

	s2 = malloc(sizeof(t_sphere));
	if (!s2)
		return (1);
	*s2 = sphere_create();
	s2->transform = m4x4_translation(0, 0, 10);
	s2->inverse = m4x4_inverse(s2->transform);
	w.spheres = spheres_add(w.spheres, s2);

	t_ray r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_intersect *i = create_intersection(SPHERE, s2, 4);

	t_comps comps = prepare_computations(r, i);
	t_color c = shade_hit(&w, comps);

	t_color cE = color(0.1, 0.1, 0.1);
	UNIT_ASSERT_EQ(compare_tuples(&c, &cE), 0);

	destroy_scene(&w);
	return (0);
}

int	test_shadow_point_offsets(void)
{
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_sphere	shape = sphere_create();
	shape.transform = m4x4_translation(0, 0, 1);
	shape.inverse = m4x4_inverse(shape.transform);

	t_intersect *i = create_intersection(SPHERE, &shape, 5.0);

	t_comps comps = prepare_computations(r, i);
	UNIT_ASSERT(comps.over_point.z < -UNIT_EPSILON / 2);
	UNIT_ASSERT(comps.point.z > comps.over_point.z);

	return (0);
}
