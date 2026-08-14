/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/14 19:12:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "data.h"
#include "minirt.h"
#include "mlx.h"

/**
 * @brief Initialize the mlx struct (not confused for mlx_init)
 * sets 0 for ints, NULL for pointers
 */
void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->img_ptr = NULL;
	mlx->img_data = NULL;
	mlx->bpp = 0;
	mlx->endian = 0;
	mlx->size_line = 0;
}

/**
 * @brief Initializes the library into the struct.
 * NOTE: data is only for key events
 */
int		init_mlx_lib(t_mlx *mlx, t_data *data)
{
	init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "Fils de Fer");
	if (!mlx->win_ptr)
		return (destroy_mlx(mlx));
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	if (!mlx->img_ptr)
		return (destroy_mlx(mlx));
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp, &mlx->size_line, &mlx->endian);
	if (!mlx->img_data)
		return (destroy_mlx(mlx));
	mlx_hook(mlx->win_ptr, 2, 1L << 0, on_key_press, data);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, on_key_release, data);
	mlx_hook(mlx->win_ptr, 17, 0, on_close, data);
	mlx_loop_hook(mlx->mlx_ptr, &render_frame, data);
	return (1);
}


/**
 * @brief Handles key inputs, calls on_close if keycode is KEY_ESC.
 *
 * @param keycode
 * @param param
 * @return int
 */
int		on_key_press(int keycode, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	if (keycode == KEY_ESC)
		on_close(param);
	if (keycode == KEY_SPACE)
		move(data, vector(0.0, 0.5, 0.0));
	if (keycode == KEY_Z)
		move(data, vector(0.0, -0.5, 0.0));
	if (keycode == KEY_W)
		move(data, vector(0.0, 0.0, -0.5));
	if (keycode == KEY_A)
		move(data, vector(0.5, 0.0, 0.0));
	if (keycode == KEY_S)
		move(data, vector(0.0, 0.0, 0.5));
	if (keycode == KEY_D)
		move(data, vector(-0.5, 0.0, 0.0));
	if (keycode == KEY_UP)
		rotate_vertical(data, 0.05);
	if (keycode == KEY_LEFT)
		rotate_horizontal(data, -0.05);
	if (keycode == KEY_DOWN)
		rotate_vertical(data, -0.05);
	if (keycode == KEY_RIGHT)
		rotate_horizontal(data, 0.05);
	return (0);
}

int		on_key_release(int keycode, void *params)
{
	(void) keycode;
	(void) params;
	return (0);
}

/**
 * @brief Destroys the data and cleanly exits the program.
 *
 * @param param
 * @return int
 */
int		on_close(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	destroy_scene(&data->scene);
	destroy_mlx(&data->mlx);
	exit(0);
	return (0);
}

/**
 * @brief Destroys and frees the mlx image, window and display.
 *        Always returns 0.
 *
 * @param mlx
 * @return int
 */
int		destroy_mlx(t_mlx *mlx)
{
	if (mlx->img_ptr)
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	if (mlx->win_ptr)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	mlx->img_ptr = NULL;
	mlx->win_ptr = NULL;
	mlx->mlx_ptr = NULL;
	return (0);
}
