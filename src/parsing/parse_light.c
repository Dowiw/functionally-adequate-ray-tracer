/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:19:46 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:45:11 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"

/**
 * Parses the given 'params' to the given 'scene's light.
 * The expected format looks like this:
 *   L <pos> <brightness> <color> (for example: L -40.0,50.0,0.0 0.6 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_light(t_scene *scene, char **params)
{
	double	brightness;
	int		rgb_color;
	t_color	intensity_color;

	if (scene->has_light)
		return (parse_error(scene, "Light is already declared"));
	if (array_len((void **) params) != 4)
		return (parse_error(scene, "Bad format, expected L <pos> <brightness> <color>"));
	if (!parse_point(scene, &scene->light.pos, params[1]))
		return (parse_error(scene, "Failed to parse position"));
	if (!parse_double_range(scene, &brightness, params[2], 0.0, 1.0))
		return (parse_error(scene, "Failed to parse brightness"));
	if (!parse_color(scene, &rgb_color, params[3]))
		return (parse_error(scene, "Failed to parse color"));
	intensity_color = color((double) red(rgb_color) * brightness / 255.0, (double) green(rgb_color) * brightness / 255.0, (double) blue(rgb_color) * brightness / 255.0);
	scene->light.intensity = intensity_color;
	scene->has_light = 1;
	return (1);
}
