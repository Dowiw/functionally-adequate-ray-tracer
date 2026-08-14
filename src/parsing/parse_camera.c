/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/08/14 18:58:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

static void	finish_camera(t_camera *camera, int width, int height);

/**
 * Parses the given 'params' to the given 'scene's camera.
 * The expected format looks like this:
 *   C <pos> <orientation> <fov> (for example: C -50.0,0,20 0,0,1 70)
 * The orientation vector is as follows:
 *   <roll>,<yaw>,<pitch>
 *
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
	t_point		to;
	t_vector	up;

	camera->width = width;
	camera->height = height;
	camera->field_of_view = camera->fov * PI / 180.0;
	to = tuples_add(camera->pos, camera->orientation);
	if (fabs(camera->orientation.x) < UNIT_EPSILON && fabs(camera->orientation.z) < UNIT_EPSILON)
		up = vector(0.0, 0.0, 1.0);
	else
		up = vector(0.0, 1.0, 0.0);
	camera->transform = view_transform(camera->pos, to, up);
	if (camera->orientation.z != 0.0)
		camera->horizontal = PI + atan(camera->orientation.x / camera->orientation.z);
	else
		camera->horizontal = PI + PI / 2.0;
	if (camera->orientation.x != 0.0 || camera->orientation.z != 0.0)
		camera->vertical = atan(camera->orientation.y / sqrt(camera->orientation.x * camera->orientation.x + camera->orientation.z * camera->orientation.z));
	else if (camera->orientation.y > 0.0)
		camera->vertical = PI * 0.5;
	else
		camera->vertical = -(PI * 0.5);
	init_camera(camera);
}
