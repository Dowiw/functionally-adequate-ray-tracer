/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 18:59:54 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "graphics.h"
#include "libft/libft.h"
#include "minirt.h"
#include "rendering.h"
#include "scene.h"
#include "types.h"

static void	update(t_data *data);

static void	update_camera(t_camera *camera);

void	move(t_data *data, t_vector vec)
{
	data->scene.camera.pos = tuples_add(data->scene.camera.pos, m4x4_multiply_tuple(m4x4_rotation_y(data->scene.camera.horizontal), vec));
	update(data);
}

void	rotate_horizontal(t_data *data, double radians)
{
	data->scene.camera.horizontal += radians;
	update(data);
}

void	rotate_vertical(t_data *data, double radians)
{
	data->scene.camera.vertical += radians;
	if (data->scene.camera.vertical < -(PI * 0.5))
		data->scene.camera.vertical = -(PI * 0.5);
	if (data->scene.camera.vertical > PI * 0.5)
		data->scene.camera.vertical = PI * 0.5;
	update(data);
}

static void	update(t_data *data)
{
	update_camera(&data->scene.camera);
	render_init(&data->iter);
	ft_bzero(data->mlx.img_data, WIN_W * WIN_H * sizeof(int));
}

static void	update_camera(t_camera *camera)
{
	camera->transform = m4x4_translation(camera->pos.x, camera->pos.y, camera->pos.z);
	camera->transform = m4x4_multiply(camera->transform, m4x4_rotation_y(camera->horizontal));
	camera->transform = m4x4_multiply(camera->transform, m4x4_rotation_x(camera->vertical));
	camera->transform = m4x4_inverse(camera->transform);
	init_camera(camera);
}
