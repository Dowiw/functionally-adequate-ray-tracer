/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:28:57 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 22:26:09 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/spheres.h"
#include "util/colors.h"

static void	finish_sphere(t_sphere *sphere);

static int	parse_sphere_error(t_scene *scene, t_sphere *sphere, char *error);

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
		return (parse_error(scene, "Expected sp <center> <diameter> <color>"));
	sphere = malloc(sizeof(t_sphere));
	if (sphere == NULL)
		return (parse_error(scene, "Allocation Failure"));
	if (!parse_point(scene, &sphere->pos, params[1]))
		return (parse_sphere_error(scene, sphere, "Failed to parse center"));
	if (!parse_double(scene, &sphere->d, params[2]))
		return (parse_sphere_error(scene, sphere, "Failed to parse diameter"));
	if (!parse_color(scene, &sphere->color, params[3]))
		return (parse_sphere_error(scene, sphere, "Failed to parse color"));
	finish_sphere(sphere);
	scene->spheres = spheres_add(scene->spheres, sphere);
	if (scene->spheres == NULL)
		return (parse_error(scene, "Allocation Failure"));
	return (1);
}

static void	finish_sphere(t_sphere *sphere)
{
	double	radius;
	t_m4x4	m;

	radius = sphere->d / 2.0;
	m = m4x4_translation(sphere->pos.x, sphere->pos.y, sphere->pos.z);
	m = m4x4_multiply(m, m4x4_scaling(radius, radius, radius));
	sphere->transform = m;
	sphere->inverse = m4x4_inverse(m);
	sphere->material = material();
	sphere->material.color = color(red(sphere->color) / 255.0,
			green(sphere->color) / 255.0,
			blue(sphere->color) / 255.0);
}

static int	parse_sphere_error(t_scene *scene, t_sphere *sphere, char *error)
{
	free(sphere);
	return (parse_error(scene, error));
}
