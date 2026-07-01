/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:19:07 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:30:21 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/cylinders.h"

static int	parse_cylinder_error(t_cylinder *cylinder);

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

	if (array_len((void **) params) != 6)
		return (0);
	cylinder = malloc(sizeof(t_cylinder));
	if (cylinder == NULL)
		return (0);
	if (!parse_vec(&cylinder->center, params[1]))
		return (parse_cylinder_error(cylinder));
	if (!parse_vec(&cylinder->vec, params[2]))
		return (parse_cylinder_error(cylinder));
	if (!parse_double(&cylinder->diameter, params[3]))
		return (parse_cylinder_error(cylinder));
	if (!parse_double(&cylinder->height, params[4]))
		return (parse_cylinder_error(cylinder));
	if (!parse_color(&cylinder->color, params[5]))
		return (parse_cylinder_error(cylinder));
	scene->cylinders = cylinders_add(scene->cylinders, cylinder);
	if (scene->cylinders == NULL)
		return (0);
	return (1);
}

static int	parse_cylinder_error(t_cylinder *cylinder)
{
	free(cylinder);
	return (0);
}
