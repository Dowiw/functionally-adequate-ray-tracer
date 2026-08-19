/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 14:39:44 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_tuple(t_tuple tuple)
{
	printf("{%f, %f, %f, %f}", tuple.x, tuple.y, tuple.z, tuple.w);
}

void	print_tuple_ln(t_tuple tuple)
{
	print_tuple(tuple);
	printf("\n");
}

void	print_m4x4_ln(t_m4x4 matrix)
{
	printf("[%f, %f, %f, %f]\n", matrix.m[0][0], matrix.m[0][1], matrix.m[0][2], matrix.m[0][3]);
	printf("[%f, %f, %f, %f]\n", matrix.m[1][0], matrix.m[1][1], matrix.m[1][2], matrix.m[1][3]);
	printf("[%f, %f, %f, %f]\n", matrix.m[2][0], matrix.m[2][1], matrix.m[2][2], matrix.m[2][3]);
	printf("[%f, %f, %f, %f]\n", matrix.m[3][0], matrix.m[3][1], matrix.m[3][2], matrix.m[3][3]);
}

void	print_material(t_material material)
{
	printf("{\n");

	printf("color: ");
	print_tuple_ln(material.color);
	printf("ambient: %f\n", material.ambient);
	printf("diffuse: %f\n", material.diffuse);
	printf("specular: %f\n", material.specular);
	printf("shininess: %f\n", material.shininess);

	printf("}\n");
}

void	print_sphere(t_sphere *sphere)
{
	if (sphere == NULL)
	{
		printf("NULL\n");
		return ;
	}

	printf("{\n");

	printf("center: ");
	print_tuple_ln(sphere->center);

	printf("material: ");
	print_material(sphere->material);

	printf("transform: ");
	print_m4x4_ln(sphere->transform);

	printf("diameter: %f", sphere->diameter);

	printf("}\n");
}

void	print_spheres(t_sphere **spheres)
{
	int	i;

	if (spheres == NULL)
	{
		printf("NULL\n");
		return ;
	}

	printf("[\n");

	i = 0;
	while (spheres[i] != NULL)
	{
		print_sphere(spheres[i]);
		if (spheres[i + 1] != NULL)
			printf(",");
		printf("\n");
		i++;
	}

	printf("]\n");
}

void	print_camera(t_camera camera)
{
	printf("{\n");

	printf("pos: ");
	print_tuple_ln(camera.pos);

	printf("orientation: ");
	print_tuple_ln(camera.orientation);

	printf("fov: %f\n", camera.fov);

	printf("transform: ");
	print_m4x4_ln(camera.transform);

	printf("field_of_view: %f\n", camera.field_of_view);

	printf("width: %d\n", camera.width);
	printf("height: %d\n", camera.height);

	printf("half_view: %f\n", camera.half_view);
	printf("aspect_ratio: %f\n", camera.aspect_ratio);
	printf("half_width: %f\n", camera.pixel_size);
	printf("half_height: %f\n", camera.half_height);
	printf("pixel_size: %f\n", camera.pixel_size);

	printf("}\n");
}

void	print_ambience(t_ambience ambience)
{
	(void) ambience;
	printf("?\n");
}

void	print_light(t_light light)
{
	printf("{\n");

	printf("pos: ");
	print_tuple_ln(light.pos);

	printf("intensity: ");
	print_tuple_ln(light.intensity);

	printf("}\n");
}

void	print_scene(t_scene *scene)
{
	if (scene == NULL)
	{
		printf("NULL\n");
		return ;
	}

	printf("{\n");

	printf("ambience: ");
	print_ambience(scene->ambience);

	printf("camera: ");
	print_camera(scene->camera);

	printf("light: ");
	print_light(scene->light);

	printf("spheres: ");
	print_spheres(scene->spheres);

	printf("}\n");
}

void	print_ray(t_ray ray)
{
	printf("{");
	printf("origin: ");
	print_tuple(ray.origin);
	printf(", direction: ");
	print_tuple(ray.dir);
	printf("}");
}

void	print_ray_ln(t_ray ray)
{
	print_ray(ray);
	printf("\n");
}

void	print_intersects(t_intersect **intersections)
{
	int	i;

	if (intersections == NULL)
	{
		printf("NULL\n");
		return ;
	}

	printf("[\n");

	i = 0;
	while (intersections[i] != NULL)
	{
		printf("%f\n", intersections[i]->t);
		if (intersections[i + 1] != NULL)
			printf(",");
		printf("\n");
		i++;
	}

	printf("]\n");
}

void	print_comps(t_comps comps)
{
	printf("{\n");

	printf("t: %f\n", comps.t);
	printf("obj: ?\n");
	printf("point: ");
	print_tuple_ln(comps.point);
	printf("eyev: ");
	print_tuple_ln(comps.eyev);
	printf("normalv: ");
	print_tuple_ln(comps.normalv);
	printf("inside: %d\n", comps.inside);

	printf("}\n");
}
