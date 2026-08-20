/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 12:57:36 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 20:57:26 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "graphics.h"
#include "minirt.h"
#include "rendering.h"

void	set_pixel(t_mlx *mlx, int x, int y, int color);

void	fill_pixel(t_mlx *mlx, t_iter *iter, int color)
{
	int	x_offset;
	int	y_offset;
	int	x;
	int	y;
	int	res;

	x = iter->x;
	y = iter->y;
	res = iter->res;
	x_offset = 0;
	while (x_offset < res)
	{
		y_offset = 0;
		while (y_offset < res)
		{
			set_pixel(mlx, x + x_offset, y + y_offset, color);
			y_offset++;
		}
		x_offset++;
	}
}

void	set_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = mlx->img_data + (y * mlx->size_line + x * (mlx->bpp / 8));
	*(int *) dst = color;
}

/**
 * @brief Updates the mlx window with the current image data.
 *
 * @param mlx
 */
void	put_frame(t_mlx mlx)
{
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_do_sync(mlx.mlx_ptr);
}
