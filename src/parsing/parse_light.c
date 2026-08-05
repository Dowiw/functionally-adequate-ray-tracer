/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:19:46 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 14:16:48 by sstark           ###   ########.fr       */
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
		return (0);
	if (array_len((void **) params) != 4)
		return (0);
	if (!parse_point(&scene->light.pos, params[1]))
		return (0);
	if (!parse_double_range(&brightness, params[2], 0.0, 1.0))
		return (0);
	if (!parse_color(&rgb_color, params[3]))
		return (0);
	intensity_color = color((double)red(rgb_color) / 255.0,
			(double)green(rgb_color) / 255.0, (double)blue(rgb_color) / 255.0);
	scene->light.intensity = tuple_mult(intensity_color, brightness);
	scene->has_light = 1;
	return (1);
}
