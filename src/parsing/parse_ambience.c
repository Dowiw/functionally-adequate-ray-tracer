/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:17:25 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:04:20 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

/**
 * Parses the given 'params' to the given 'scene's ambience.
 * The expected format looks like this:
 *   A <lighting> <color> (for example: A 0.2 255,255,255)
 * Returns true if the parsing was succesful.
 */
int	parse_ambience(t_scene *scene, char **params)
{
	if (scene->has_ambience)
		return (parse_error(scene, "Ambience is already declared"));
	if (array_len((void **) params) != 3)
		return (parse_error(scene, "Expected C <pos> <orientation> <fov>"));
	if (!parse_double_range(scene, &scene->ambience.lighting, params[1], 0, 1))
		return (parse_error(scene, "Failed to parse lighting"));
	if (!parse_color(scene, &scene->ambience.color, params[2]))
		return (parse_error(scene, "Failed to parse color"));
	scene->has_ambience = 1;
	return (1);
}
