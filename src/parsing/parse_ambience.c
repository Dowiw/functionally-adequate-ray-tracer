/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambience.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:17:25 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 11:53:44 by sstark           ###   ########.fr       */
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
		return (0);
	if (array_len((void **) params) != 3)
		return (0);
	if (!parse_double_range(&scene->ambience.lighting, params[1], 0.0, 1.0))
		return (0);
	if (!parse_color(&scene->ambience.color, params[2]))
		return (0);
	scene->has_ambience = 1;
	return (1);
}
