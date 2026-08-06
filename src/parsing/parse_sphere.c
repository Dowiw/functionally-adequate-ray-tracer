/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:28:57 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 19:15:38 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/spheres.h"
#include "util/colors.h"

static void	finish_sphere(t_sphere *sphere);

static int	parse_sphere_error(t_sphere *sphere);

/**
 * Parses the given 'params' and adds it to the scenes spheres.
 * The expected format looks like this:
 *   sp <center> <diameter> <color> (for example: sp 0.0,0.0,20.6 12.6 10,0,255)
 * Returns true if the parsing was succesful.
 */
int	parse_sphere(t_scene *scene, char **params)
{
	t_sphere	*sphere;

	if (array_len((void **) params) != 4)
		return (0);
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (0);
	if (!parse_point(&sphere->center, params[1]))
		return (parse_sphere_error(sphere));
	if (!parse_double(&sphere->diameter, params[2]))
		return (parse_sphere_error(sphere));
	if (!parse_color(&sphere->color, params[3]))
		return (parse_sphere_error(sphere));
	finish_sphere(sphere);
	scene->spheres = spheres_add(scene->spheres, sphere);
	if (scene->spheres == NULL)
		return (0);
	return (1);
}

static void	finish_sphere(t_sphere *sphere)
{
	sphere->transform = matrix4x4_translation(sphere->center.x, sphere->center.y, sphere->center.z);
	sphere->transform = matrix4x4_multiply(sphere->transform, matrix4x4_scaling(sphere->diameter, sphere->diameter, sphere->diameter));
	sphere->material = material();
	sphere->material.color = color(red(sphere->color) / 255.0, green(sphere->color) / 255.0, blue(sphere->color) / 255.0);
}

static int	parse_sphere_error(t_sphere *sphere)
{
	free(sphere);
	return (0);
}
