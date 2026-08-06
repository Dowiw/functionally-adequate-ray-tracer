/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:25:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:00:47 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"

void	render_scene(t_canvas *canvas, t_scene *scene)
{
	int		x;
	int		y;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			write_pixel(canvas, x, y, color_at(scene, ray_for_pixel(scene->camera, x, y)));
			x++;
		}
		y++;
	}
}
