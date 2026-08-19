/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:28:49 by sstark            #+#    #+#             */
/*   Updated: 2026/08/16 15:56:22 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"
#include "util/planes.h"
#include <stdlib.h>

static void finish_plane(t_plane *plane, int rgb_color);
static int parse_plane_error(t_scene *scene, t_plane *plane, char *error);

/**
 * Parses the given 'params' and adds it to the scenes planes.
 * The expected format looks like this:
 *   pl <pos> <vector> <color>
 *   (for example: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225)
 * Returns true if the parsing was succesful.
 */
int parse_plane(t_scene *scene, char **params)
{
	t_plane *plane;
	int rgb_color;

	if (array_len((void **)params) != 4)
		return (parse_error(scene,
							"Bad format, expected pl <pos> <vector> <color>"));
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &plane->pos, params[1]))
		return (parse_plane_error(scene, plane, "Failed to parse position"));
	if (!parse_vector(scene, &plane->vec, params[2]))
		return (parse_plane_error(scene, plane, "Failed to parse vector"));
	if (!parse_color(scene, &rgb_color, params[3]))
		return (parse_plane_error(scene, plane, "Failed to parse color"));
	finish_plane(plane, rgb_color);
	scene->planes = planes_add(scene->planes, plane);
	if (scene->planes == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

static void finish_plane(t_plane *plane, int rgb_color)
{
	plane->transform =
		matrix4x4_translation(plane->pos.x, plane->pos.y, plane->pos.z);
	plane->inverse = matrix4x4_inverse(plane->transform);
	plane->material = material();
	plane->material.color =
		color(red(rgb_color) / 255.0, green(rgb_color) / 255.0,
			  blue(rgb_color) / 255.0);
}

static int parse_plane_error(t_scene *scene, t_plane *plane, char *error)
{
	free(plane);
	return (parse_error(scene, error));
}
