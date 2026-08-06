/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:57:11 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

static void	finish_camera(t_camera *camera, int width, int height);

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
	finish_camera(&scene->camera, WIN_W, WIN_H);
	scene->has_camera = 1;
	return (1);
}

static void	finish_camera(t_camera *camera, int width, int height)
{
	camera->width = width;
	camera->height = height;
	camera->field_of_view = camera->fov * PI / 180.0;
	// TODO
	// camera->transform = view_transform(camera->pos, ?, ?);
	camera->transform = matrix4x4_identity();
	init_camera(camera);
}
