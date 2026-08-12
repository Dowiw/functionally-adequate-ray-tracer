/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:25:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/12 18:11:37 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <mlx.h>
#include "data.h"
#include "debug.h"
#include "minirt.h"
#include "ray.h"
#include "rendering.h"
#include "scene.h"
#include "util/colors.h"

static void	render_pixel(t_data *data);

static void	put_frame(t_mlx mlx);

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

/**
 * @brief Initializes the iteration struct used for rendering across multiple frames.
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
 * @brief Renders the amount of new pixels specified in data.iter.pixels_per_frame.
 *        The mlx window is updated at the end of the frame.
 *        If the scene has already finished rendering, this function returns immediately.
 *
 * @param data
 * @return int
 */
	#include <stdlib.h>
int		render_frame(t_data *data)
{
	t_iter	*iter;

	iter = &data->iter;
	if (iter->res == 0)
		exit (0);
	iter->pixels = 0;
	while (iter->res > 0)
	{
		while (iter->x < WIN_W)
		{
			while (iter->y < WIN_H)
			{
				render_pixel(data);
				iter->y += iter->res;
				if (iter->pixels >= PIXELS_PER_FRAME)
					return (0);
			}
			iter->x += iter->res;
			iter->y = 0;
		}
		iter->x = 0;
		iter->res = iter->res / 2;
		iter->first = 0;
		put_frame(data->mlx);
		return (0);
	}
	return (0);
}

/**
 * @brief Renders the pixel at the current iteration stored in data.iter.
 *
 * @param data
 */
static void	render_pixel(t_data *data)
{
	t_iter	*iter;
	t_ray	ray;
	t_color	color;
	int		color_rgb;

	iter = &data->iter;
	if (!iter->first && iter->x % (iter->res * 2) == 0 && iter->y % (iter->res * 2) == 0)
		return ;
	ray = ray_for_pixel(data->scene.camera, iter->x, iter->y);
	color = color_at(&data->scene, ray);
	color_rgb = rgb(clamp_color(color.x), clamp_color(color.y), clamp_color(color.z));
	fill_pixel(&data->mlx, iter->res, iter->x, iter->y, color_rgb);
	iter->pixels++;
}

/**
 * @brief Updates the mlx window with the current image data.
 *
 * @param mlx
 * @return int
 */
static void	put_frame(t_mlx mlx)
{
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
}
