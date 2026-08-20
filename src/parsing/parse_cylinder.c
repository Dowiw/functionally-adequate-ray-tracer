/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:19:07 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 22:26:09 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"
#include "util/cylinders.h"

static void	finish_cylinder(t_cylinder *cyl, int rgb_color);

static int	parse_cylinder_error(t_scene *scene, t_cylinder *cyl, char *error);

/**
 * Parses the given 'params' and adds it to the scenes cylinders.
 * The expected format looks like this:
 *   cy <center> <vector> <diameter> <height> <color>
 *   (for example: cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_cylinder(t_scene *scene, char **params)
{
	t_cylinder	*cyl;
	int			rgb_color;

	if (array_len((void **) params) != 6)
		return (parse_error(scene,
				"Expected cy <center> <vector> <diameter> <height> <color>"));
	cyl = malloc(sizeof(t_cylinder));
	if (cyl == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &cyl->pos, params[1]))
		return (parse_cylinder_error(scene, cyl, "Failed to parse center"));
	if (!parse_vector(scene, &cyl->vec, params[2]))
		return (parse_cylinder_error(scene, cyl, "Failed to parse vector"));
	if (!parse_double(scene, &cyl->d, params[3]))
		return (parse_cylinder_error(scene, cyl, "Failed to parse diameter"));
	if (!parse_double(scene, &cyl->height, params[4]))
		return (parse_cylinder_error(scene, cyl, "Failed to parse height"));
	if (!parse_color(scene, &rgb_color, params[5]))
		return (parse_cylinder_error(scene, cyl, "Failed to parse color"));
	finish_cylinder(cyl, rgb_color);
	scene->cylinders = cylinders_add(scene->cylinders, cyl);
	if (scene->cylinders == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

/**
 * @brief Finalizes a cylinder by computing its transformation matrix.
 * Sets up translation, rotation, and scaling matrices based on orientation.
 *
 * @param cylinder pointer to the cylinder to finalize
 * @param norm the orientation normal vector
 * @param pos the position of the cylinder
 * @param d the diameter of the cylinder
 */
static void	finish_cylinder(t_cylinder *cyl, int rgb_color)
{
	t_m4x4	m;

	m = m4x4_translation(cyl->pos.x, cyl->pos.y, cyl->pos.z);
	m = m4x4_multiply(m, m4x4_rotation(cyl->vec));
	m = m4x4_multiply(m, m4x4_scaling(cyl->d / 2, cyl->height, cyl->d / 2));
	cyl->transform = m;
	cyl->inverse = m4x4_inverse(m);
	cyl->min = -0.5;
	cyl->max = 0.5;
	cyl->closed = 1;
	cyl->material = material();
	cyl->material.color = color(red(rgb_color) / 255.0,
			green(rgb_color) / 255.0,
			blue(rgb_color) / 255.0);
}

/**
 * @brief Helper to handle parsing errors for cylinders and free memory.
 *
 * @param error string describing the error
 * @param arr split string array to free
 * @param scene scene pointer for error logging
 * @return 0 indicating failure
 */
static int	parse_cylinder_error(t_scene *scene, t_cylinder *cyl, char *error)
{
	free(cyl);
	return (parse_error(scene, error));
}
