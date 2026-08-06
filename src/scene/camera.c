/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/06 15:19:02 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:41:15 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "scene.h"

/**
 * @brief Creates a new camera with the given parameters
 *
 * @param width
 * @param height
 * @param fov
 * @return t_camera
 */
t_camera	create_camera(int width, int height, double fov)
{
	t_camera	result;

	result.width = width;
	result.height = height;
	result.field_of_view = fov;
	result.transform = matrix4x4_identity();
	init_camera(&result);
	return (result);
}

/**
 * @brief Initializes a camera based on its values from parsing
 *
 * @param camera
 */
void		init_camera(t_camera *camera)
{
	camera->half_view = tan(camera->field_of_view / 2.0);
	camera->aspect_ratio = ((double) camera->width) / camera->height;
	if (camera->aspect_ratio >= 1.0)
	{
		camera->half_width = camera->half_view;
		camera->half_height = camera->half_view / camera->aspect_ratio;
	}
	else
	{
		camera->half_width = camera->half_view * camera->aspect_ratio;
		camera->half_height = camera->half_view;
	}
	camera->pixel_size = (camera->half_width * 2.0) / camera->width;
}

void		finish_camera(t_camera *camera, int width, int height)
{
	camera->width = width;
	camera->height = height;
	camera->field_of_view = camera->fov * PI / 180.0;
	// TODO
	// camera->transform = view_transform(camera->pos, ?, ?);
	camera->transform = matrix4x4_identity();
	init_camera(camera);
}
