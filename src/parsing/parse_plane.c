/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:28:49 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:31:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/planes.h"

static int	parse_plane_error(t_plane *plane);

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
		return (0);
	plane = malloc(sizeof(t_plane));
	if (plane == NULL)
		return (0);
	if (!parse_vec(&plane->pos, params[1]))
		return (parse_plane_error(plane));
	if (!parse_vec(&plane->vec, params[2]))
		return (parse_plane_error(plane));
	if (!parse_color(&plane->color, params[3]))
		return (parse_plane_error(plane));
	scene->planes = planes_add(scene->planes, plane);
	if (scene->planes == NULL)
		return (0);
	return (1);
}

static int	parse_plane_error(t_plane *plane)
{
	free(plane);
	return (0);
}
