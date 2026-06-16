/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 13:31:45 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (array_len((void **) params) != 4)
		return (0);
	if (!parse_vec(&scene->camera.pos, params[1]))
		return (0);
	if (!parse_vec(&scene->camera.orientation, params[2]))
		return (0);
	if (!parse_double_range(&scene->camera.fov, params[3], 0, 180))
		return (0);
	return (1);
}
