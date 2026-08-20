/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:03:29 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 22:26:09 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "graphics.h"
#include "minirt.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

static void		finish_camera(t_camera *camera, int width, int height);

static double	calculate_horizontal(t_vector vec);

static double	calculate_vertical(t_vector vec);

/**
 * Parses the given 'params' to the given 'scene's camera.
 * The expected format looks like this:
 *   C <pos> <orientation> <fov> (for example: C -50.0,0,20 0,0,1 70)
 * The orientation vector is as follows:
 *   <roll>,<yaw>,<pitch>
 *
 * Returns true if the parsing was succesful.
 */
int	parse_camera(t_scene *scene, char **params)
{
	if (scene->has_camera)
		return (parse_error(scene, "Camera is already declared"));
	if (array_len((void **) params) != 4)
		return (parse_error(scene, "Expected C <pos> <orientation> <fov>"));
	if (!parse_point(scene, &scene->camera.pos, params[1]))
		return (parse_error(scene, "Failed to parse position"));
	if (!parse_direction(scene, &scene->camera.orientation, params[2]))
		return (parse_error(scene, "Failed to parse orientation"));
	if (!parse_double_range(scene, &scene->camera.fov, params[3],
			(double [2]){0.0, 500.0}))
		return (parse_error(scene, "Failed to parse fov"));
	finish_camera(&scene->camera, WIN_W, WIN_H);
	scene->has_camera = 1;
	return (1);
}

/**
 * @brief Finishes camera setup by computing the transform and pixel size.
 * Calculates the half width and height based on the aspect ratio and FOV,
 * and sets up the view transformation matrix.
 *
 * @param camera pointer to the camera structure to finalize
 */
static void	finish_camera(t_camera *cam, int width, int height)
{
	cam->width = width;
	cam->height = height;
	cam->field_of_view = cam->fov * PI / 180.0;
	cam->horizontal = calculate_horizontal(cam->orientation);
	cam->vertical = calculate_vertical(cam->orientation);
	cam->transform = m4x4_translation(cam->pos.x, cam->pos.y, cam->pos.z);
	cam->transform = m4x4_multiply(cam->transform,
			m4x4_rotation_y(cam->horizontal));
	cam->transform = m4x4_multiply(cam->transform,
			m4x4_rotation_x(cam->vertical));
	cam->transform = m4x4_inverse(cam->transform);
	init_camera(cam);
}

/**
 * @brief Calculates the horizontal component (right vector) of the camera.
 * Used when constructing the view transformation matrix to align the camera.
 *
 * @param forward the forward direction vector
 * @return the normalized right vector (horizontal axis)
 */
static double	calculate_horizontal(t_vector vec)
{
	if (vec.z == 0.0)
	{
		if (vec.x > 0.0)
			return (PI * 1.5);
		return (PI * 0.5);
	}
	if (vec.z > 0.0)
		return (PI * 1.0 + atan(vec.x / vec.z));
	return (PI * 0.0 + atan(vec.x / vec.z));
}

/**
 * @brief Calculates the vertical component (up vector) of the camera.
 * Crosses the horizontal and forward vectors to find the true up vector.
 *
 * @param horizontal the computed right vector
 * @param forward the forward direction vector
 * @return the normalized up vector (vertical axis)
 */
static double	calculate_vertical(t_vector vec)
{
	if (vec.x != 0.0 || vec.z != 0.0)
		return (atan(vec.y / sqrt(vec.x * vec.x + vec.z * vec.z)));
	if (vec.y > 0.0)
		return (PI * 0.5);
	return (PI * -0.5);
}
