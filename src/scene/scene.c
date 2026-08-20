/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:15:24 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:47:49 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/cylinders.h"
#include "util/planes.h"
#include "util/spheres.h"
#include "util/cones.h"

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
	scene->cones = cones_create();
	scene->ambience = (t_ambience){0.0, 0};
	scene->has_ambience = 0;
	scene->has_camera = 0;
	scene->has_light = 0;
	ft_bzero(scene->error, ERROR_STACK_SIZE + 1);
	scene->error_line = NULL;
	if (scene->cylinders == NULL || scene->planes == NULL
		|| scene->spheres == NULL || scene->cones == NULL)
	{
		destroy_scene(scene);
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
	free_cones(scene->cones);
	scene->cylinders = NULL;
	scene->planes = NULL;
	scene->spheres = NULL;
	scene->cones = NULL;
}
