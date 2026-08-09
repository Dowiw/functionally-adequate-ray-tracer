/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:34:32 by sstark           ###   ########.fr       */
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
		return (parse_error(scene, "Camera is already declared"));
	if (array_len((void **) params) != 4)
		return (parse_error(scene, "Bad format, expected C <pos> <orientation> <fov>"));
	if (!parse_point(scene, &scene->camera.pos, params[1]))
		return (parse_error(scene, "Failed to parse position"));
	if (!parse_vector(scene, &scene->camera.orientation, params[2]))
		return (parse_error(scene, "Failed to parse orientation"));
	if (!parse_double_range(scene, &scene->camera.fov, params[3], 0, 500))
		return (parse_error(scene, "Failed to parse fov"));
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
	// camera->orientation.w = POINT;
	// camera->transform = matrix4x4_multiply(camera->transform, view_transform(point(0.0, 0.0, 0.0), camera->orientation, point(0.0, 1.0, 0.0)));
	camera->transform = matrix4x4_translation(camera->pos.x, camera->pos.y, camera->pos.z);
	camera->transform = matrix4x4_multiply(camera->transform, matrix4x4_rotation_x(camera->orientation.x * PI));
	camera->transform = matrix4x4_multiply(camera->transform, matrix4x4_rotation_y(camera->orientation.y * PI));
	camera->transform = matrix4x4_multiply(camera->transform, matrix4x4_rotation_z(camera->orientation.z * PI));
	// camera->transform = matrix4x4_identity();
	// camera->transform = matrix4x4_multiply(camera->transform, matrix4x4_rotation_y(0.25 * PI));
	init_camera(camera);
}
