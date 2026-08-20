/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:25:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 20:40:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "graphics.h"
#include "input.h"
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "util/colors.h"

static void	render_pixel(t_data *data);

/**
 * @brief Renders the given scene onto the given canvas (who could've guessed?)
 *
 * @param canvas
 * @param scene
 */
void	render_scene(t_canvas *canvas, t_scene *scene)
{
	int		x;
	int		y;
	t_ray	r;

	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			r = ray_for_pixel(scene->camera, x, y);
			write_pixel(canvas, x, y, color_at(scene, r));
			x++;
		}
		y++;
	}
}

/**
 * @brief Initializes the iteration struct used for rendering
 *        across multiple frames.
 *
 * @param iter
 */
void	render_init(t_iter *iter)
{
	iter->res = 16;
	iter->first = 1;
	iter->x = 0;
	iter->y = 0;
	iter->pixels = 0;
}

/**
 * @brief The main MLX render loop hook. Iteratively renders the image frame
 * by frame.
 * Enables smooth interactive rendering and handles progressive rendering
 * updates.
 *
 * @param data pointer to the main data struct
 * @return 0 on success
 */
int	render_loop(t_data *data)
{
	tick_input(data);
	render_frame(data);
	return (0);
}

/**
 * @brief Renders the amount of new pixels specified in PIXELS_PER_FRAME.
 *        The mlx window is updated at the end of the frame.
 *        Returns immediately if the scene has already finished rendering.
 *
 * @param data
 * @return int
 */
void	render_frame(t_data *data)
{
	t_iter	*iter;

	iter = &data->iter;
	iter->pixels = 0;
	while (iter->res > 0)
	{
		while (iter->x < WIN_W)
		{
			while (iter->y < WIN_H)
			{
				render_pixel(data);
				iter->y += iter->res;
				if (!iter->first && iter->pixels >= PIXELS_PER_FRAME)
					return ;
			}
			iter->x += iter->res;
			iter->y = 0;
		}
		iter->x = 0;
		iter->res = iter->res / 2;
		iter->first = 0;
		put_frame(data->mlx);
		return ;
	}
	return ;
}

/**
 * @brief Computes the color for a single pixel by firing a ray through the
 * scene.
 *
 * @param iter pointer to the rendering iteration details
 * @param data pointer to the main data struct (scene, camera, mlx)
 */
static void	render_pixel(t_data *data)
{
	t_iter	*iter;
	t_ray	ray;
	t_color	color;
	int		color_rgb;

	iter = &data->iter;
	if (!iter->first && iter->x % (iter->res * 2) == 0
		&& iter->y % (iter->res * 2) == 0)
		return ;
	ray = ray_for_pixel(data->scene.camera, iter->x, iter->y);
	color = color_at(&data->scene, ray);
	color_rgb = rgb(clamp_color(color.x), clamp_color(color.y),
			clamp_color(color.z));
	fill_pixel(&data->mlx, iter, color_rgb);
	iter->pixels++;
}
