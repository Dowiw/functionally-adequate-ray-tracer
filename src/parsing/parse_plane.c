/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:28:49 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:48:57 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/planes.h"

static int	parse_plane_error(t_scene *scene, t_plane *plane, char *error);

/**
 * Parses the given 'params' and adds it to the scenes planes.
 * The expected format looks like this:
 *   pl <pos> <vector> <color>
 *   (for example: pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225)
 * Returns true if the parsing was succesful.
 */
int	parse_plane(t_scene *scene, char **params)
{
	t_plane	*plane;

	if (array_len((void **) params) != 4)
		return (parse_error(scene, "Bad format, expected pl <pos> <vector> <color>"));
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &plane->pos, params[1]))
		return (parse_plane_error(scene, plane, "Failed to parse position"));
	if (!parse_vector(scene, &plane->vec, params[2]))
		return (parse_plane_error(scene, plane, "Failed to parse vector"));
	// TODO
	// if (!parse_color(&plane->color, params[3]))
	// 	return (parse_plane_error(plane));
	scene->planes = planes_add(scene->planes, plane);
	if (scene->planes == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

static int	parse_plane_error(t_scene *scene, t_plane *plane, char *error)
{
	free(plane);
	return (parse_error(scene, error));
}
