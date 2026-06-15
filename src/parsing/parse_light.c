/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:19:46 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

/**
 * Parses the given 'params' to the given 'scene's light.
 * The expected format looks like this:
 *   L <pos> <brightness> <color> (for example: L -40.0,50.0,0.0 0.6 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_light(t_scene *scene, char **params)
{
	if (array_len((void **) params) != 4)
		return (0);
	if (!parse_vec(&scene->light.pos, params[1]))
		return (0);
	if (!parse_double(&scene->light.brightness, params[2]))
		return (0);
	if (!parse_color(&scene->light.color, params[3]))
		return (0);
	return (1);
}
