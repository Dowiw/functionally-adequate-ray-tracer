/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:15:24 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 13:52:00 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/cylinders.h"
#include "util/planes.h"
#include "util/spheres.h"

/**
 * @brief Initialize a scene structure
 *
 * @param scene
 * @return returns 0 on fail, 1 on success
 */
int	init_scene(t_scene *scene)
{
	scene->cylinders = cylinders_create();
	scene->planes = planes_create();
	scene->spheres = spheres_create();
	scene->has_ambience = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	if (scene->cylinders == NULL || scene->planes == NULL
		|| scene->spheres == NULL)
	{
		destroy_scene(scene);
		scene->cylinders = NULL;
		scene->planes = NULL;
		scene->spheres = NULL;
		return (0);
	}
	return (1);
}
/**
 * @brief Initializes the default scene
 *
 * @note has_ambience, has_camera and has_light will remain unset
 *
 * @param scene
 * @return returns 0 on fail, 1 on success
 */
int	default_scene(t_scene *scene)
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
		sphere->transform = matrix4x4_scaling(0.5, 0.5, 0.5);
	}
	scene->spheres = spheres_add(scene->spheres, sphere);
	if (scene->spheres == NULL)
	{
		destroy_scene(scene);
		scene->cylinders = NULL;
		scene->planes = NULL;
		scene->spheres = NULL;
		return (0);
	}
	return (1);
}

/**
 * @brief Frees the scene structure
 *
 * @param scene
 */
void	destroy_scene(t_scene *scene)
{
	free_cylinders(scene->cylinders);
	free_planes(scene->planes);
	free_spheres(scene->spheres);
}

/**
 * @brief Initializes a new camera with the given parameters
 *
 * @param width
 * @param height
 * @param fov
 * @return t_camera
 */
t_camera	create_camera(int width, int height, double fov)
{
	t_camera	result;

	// TODO: set pos and orientation, currently they are still unused in finish_camera
	result.fov = fov;
	finish_camera(&result, width, height);
	return (result);
}
