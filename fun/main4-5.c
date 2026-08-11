/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 14:31:04 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:04:27 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rendering.h"
#include "scene.h"
#include "util/spheres.h"

int	main(void)
{
	t_scene		scene;
	t_sphere	floor;
	t_sphere	left_wall;
	t_sphere	right_wall;
	t_sphere	middle;
	t_sphere	right;
	t_sphere	left;
	t_canvas	canvas;

	if (!init_scene(&scene))
		return (1);

	floor = sphere_create();
	floor.transform = matrix4x4_scaling(10.0, 0.01, 10.0);
	floor.material = material();
	floor.material.color = color(1.0, 0.9, 0.9);
	floor.material.specular = 0.0;

	left_wall = sphere_create();
	left_wall.transform = matrix4x4_translation(0.0, 0.0, 5.0);
	left_wall.transform = matrix4x4_multiply(left_wall.transform, matrix4x4_rotation_y(-PI / 4.0));
	left_wall.transform = matrix4x4_multiply(left_wall.transform, matrix4x4_rotation_x(PI / 2.0));
	left_wall.transform = matrix4x4_multiply(left_wall.transform, matrix4x4_scaling(10.0, 0.01, 10.0));
	left_wall.material = floor.material;

	right_wall = sphere_create();
	right_wall.transform = matrix4x4_translation(0.0, 0.0, 5.0);
	right_wall.transform = matrix4x4_multiply(right_wall.transform, matrix4x4_rotation_y(PI / 4.0));
	right_wall.transform = matrix4x4_multiply(right_wall.transform, matrix4x4_rotation_x(PI / 2.0));
	right_wall.transform = matrix4x4_multiply(right_wall.transform, matrix4x4_scaling(10.0, 0.01, 10.0));
	right_wall.material = floor.material;

	middle = sphere_create();
	middle.transform = matrix4x4_translation(-0.5, 1.0, 0.5);
	middle.material = material();
	middle.material.color = color(0.1, 1.0, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	right = sphere_create();
	right.transform = matrix4x4_translation(1.5, 0.5, -0.5);
	right.transform = matrix4x4_multiply(right.transform, matrix4x4_scaling(0.5, 0.5, 0.5));
	right.material = material();
	right.material.color = color(0.5, 1.0, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	left = sphere_create();
	left.transform = matrix4x4_translation(-1.5, 0.33, -0.75);
	left.transform = matrix4x4_multiply(left.transform, matrix4x4_scaling(0.33, 0.33, 0.33));
	left.material = material();
	left.material.color = color(1.0, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	scene.spheres = spheres_add(scene.spheres, &floor);
	scene.spheres = spheres_add(scene.spheres, &left_wall);
	scene.spheres = spheres_add(scene.spheres, &right_wall);
	scene.spheres = spheres_add(scene.spheres, &middle);
	scene.spheres = spheres_add(scene.spheres, &right);
	scene.spheres = spheres_add(scene.spheres, &left);

	scene.light = (t_light){point(-10.0, 10.0, -10.0), color(1.0, 1.0, 1.0)};

	scene.camera = create_camera(1000, 500, PI / 3);
	scene.camera.transform = view_transform(point(0.0, 1.5, -5.0), point(0.0, 1.0, 0.0), vector(0.0, 1.0, 0.0));

	if (!canvas_create(&canvas, scene.camera.width, scene.camera.height))
		return (1);

	render_scene(&canvas, &scene);
	canvas_to_ppm(&canvas);

	return (0);
}
