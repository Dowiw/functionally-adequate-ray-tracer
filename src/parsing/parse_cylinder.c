/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:19:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 16:19:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"
#include "util/cylinders.h"

static void	finish_cylinder(t_cylinder *cylinder, int rgb_color);

static int	parse_cylinder_error(t_scene *scene, t_cylinder *cylinder, char *error);

/**
 * Parses the given 'params' and adds it to the scenes cylinders.
 * The expected format looks like this:
 *   cy <center> <vector> <diameter> <height> <color>
 *   (for example: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_cylinder(t_scene *scene, char **params)
{
	t_cylinder	*cylinder;
	int			rgb_color;

	if (array_len((void **) params) != 6)
		return (parse_error(scene, "Bad format, expected cy <center> <vector> <diameter> <height> <color>"));
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &cylinder->center, params[1]))
		return (parse_cylinder_error(scene, cylinder, "Failed to parse center"));
	if (!parse_vector(scene, &cylinder->vec, params[2]))
		return (parse_cylinder_error(scene, cylinder, "Failed to parse vector"));
	if (!parse_double(scene, &cylinder->diameter, params[3]))
		return (parse_cylinder_error(scene, cylinder, "Failed to parse diameter"));
	if (!parse_double(scene, &cylinder->height, params[4]))
		return (parse_cylinder_error(scene, cylinder, "Failed to parse height"));
	if (!parse_color(scene, &rgb_color, params[5]))
		return (parse_cylinder_error(scene, cylinder, "Failed to parse color"));
	finish_cylinder(cylinder, rgb_color);
	scene->cylinders = cylinders_add(scene->cylinders, cylinder);
	if (scene->cylinders == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

static void	finish_cylinder(t_cylinder *cylinder, int rgb_color)
{
	cylinder->transform = matrix4x4_translation(cylinder->center.x, cylinder->center.y, cylinder->center.z);
	cylinder->transform = matrix4x4_multiply(cylinder->transform, matrix4x4_rotation(cylinder->vec));
	cylinder->transform = matrix4x4_multiply(cylinder->transform, matrix4x4_scaling(cylinder->diameter / 2.0, cylinder->height, cylinder->diameter / 2.0));
	cylinder->inverse = matrix4x4_inverse(cylinder->transform);
	cylinder->min = -0.5;
	cylinder->max = 0.5;
	cylinder->closed = 1;
	cylinder->material = material();
	cylinder->material.color = color(red(rgb_color) / 255.0, green(rgb_color) / 255.0, blue(rgb_color) / 255.0);
}

static int	parse_cylinder_error(t_scene *scene, t_cylinder *cylinder, char *error)
{
	free(cylinder);
	return (parse_error(scene, error));
}
