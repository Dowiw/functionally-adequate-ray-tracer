/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:06:00 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

/**
 * Parses the given 'params' to the given 'scene's camera.
 * The expected format looks like this:
 *   C <pos> <orientation> <fov> (for example: C -50.0,0,20 0,0,1 70)
 * Returns true if the parsing was succesful.
 */
int	parse_camera(t_scene *scene, char **params)
{
	if (scene->has_camera)
		return (0);
	if (array_len((void **) params) != 4)
		return (0);
	if (!parse_point(&scene->camera.pos, params[1]))
		return (0);
	if (!parse_vector(&scene->camera.orientation, params[2]))
		return (0);
	if (!parse_double_range(&scene->camera.fov, params[3], 0, 180))
		return (0);
	if (!finish_camera(&scene->camera, WIN_W, WIN_H))
		return (0);
	scene->has_camera = 1;
	return (1);
}

// TODO: camera transform
int	finish_camera(t_camera *camera, int width, int height)
{
	// TODO: apply camera position and orientation
	// camera->transform = view_transform(point(50.0, 50.0, 0.0), point(50.0, 50.0, 1.0), vector(0.0, 1.0, 0.0));
	camera->transform = matrix4x4_identity();
	camera->width = width;
	camera->height = height;
	camera->half_view = tan(camera->fov / 2.0);
	camera->aspect_ratio = ((double) width) / height;
	if (camera->aspect_ratio >= 1.0)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect_ratio;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect_ratio;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (camera->half_width * 2.0) / width;
	return (1);
}
