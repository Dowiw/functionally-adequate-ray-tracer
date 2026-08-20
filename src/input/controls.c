/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 18:59:54 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 20:57:26 by kmonjard         ###   ########.fr       */
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
	t_camera	*camera;

	camera = &data->scene.camera;
	vec = m4x4_multiply_tuple(m4x4_rotation_y(camera->horizontal), vec);
	data->scene.camera.pos = tuples_add(data->scene.camera.pos, vec);
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
	t_m4x4	m;

	m = m4x4_translation(camera->pos.x, camera->pos.y, camera->pos.z);
	m = m4x4_multiply(m, m4x4_rotation_y(camera->horizontal));
	m = m4x4_multiply(m, m4x4_rotation_x(camera->vertical));
	m = m4x4_inverse(m);
	camera->transform = m;
	init_camera(camera);
}
