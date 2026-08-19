/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 19:36:41 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:41:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"
#include "util/cones.h"

static void	finish_cone(t_cone *cone, int rgb_color);

static int	parse_cone_error(t_scene *scene, t_cone *cone, char *error);

/**
 * Parses the given 'params' and adds it to the scenes cones.
 * The expected format looks like this:
 *   co <center> <vector> <diameter> <height> <color>
 *   (for example: co 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_cone(t_scene *scene, char **params)
{
	t_cone	*cone;
	int		rgb_color;

	if (array_len((void **) params) != 6)
		return (parse_error(scene,
				"Expected cy <center> <vector> <diameter> <height> <color>"));
	cone = malloc(sizeof(t_cone));
	if (cone == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &cone->pos, params[1]))
		return (parse_cone_error(scene, cone, "Failed to parse center"));
	if (!parse_vector(scene, &cone->vec, params[2]))
		return (parse_cone_error(scene, cone, "Failed to parse vector"));
	if (!parse_double(scene, &cone->d, params[3]))
		return (parse_cone_error(scene, cone, "Failed to parse diameter"));
	if (!parse_double(scene, &cone->height, params[4]))
		return (parse_cone_error(scene, cone, "Failed to parse height"));
	if (!parse_color(scene, &rgb_color, params[5]))
		return (parse_cone_error(scene, cone, "Failed to parse color"));
	finish_cone(cone, rgb_color);
	scene->cones = cones_add(scene->cones, cone);
	if (scene->cones == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

static void	finish_cone(t_cone *cone, int rgb_color)
{
	t_m4x4	m;

	m = m4x4_translation(cone->pos.x, cone->pos.y, cone->pos.z);
	m = m4x4_multiply(m, m4x4_rotation(cone->vec));
	m = m4x4_multiply(m, m4x4_translation(0.0, cone->height / 2.0, 0.0));
	m = m4x4_multiply(m, m4x4_scaling(cone->d / 2, cone->height, cone->d / 2));
	cone->transform = m;
	cone->inverse = m4x4_inverse(m);
	cone->min = -1.0;
	cone->max = 0.0;
	cone->closed = 1;
	cone->material = material();
	cone->material.color = color(red(rgb_color) / 255.0, green(rgb_color) / 255.0, blue(rgb_color) / 255.0);
}

static int	parse_cone_error(t_scene *scene, t_cone *cone, char *error)
{
	free(cone);
	return (parse_error(scene, error));
}
