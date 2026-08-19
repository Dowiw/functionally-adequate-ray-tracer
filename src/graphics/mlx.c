/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 17:33:31 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "graphics.h"
#include "input.h"
#include "rendering.h"
#include "scene.h"
#include "types.h"

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
	mlx_loop_hook(mlx->mlx_ptr, &render_loop, data);
	return (1);
}

int		on_key_press(int keycode, void *param)
{
	t_input	*input;

	input = &((t_data *) param)->input;
	if (keycode == KEY_ESC)
		on_close(param);
	if (keycode == KEY_SPACE)
		input->key_space = 1;
	if (keycode == KEY_SHIFT)
		input->key_shift = 1;
	if (keycode == KEY_W)
		input->key_w = 1;
	if (keycode == KEY_A)
		input->key_a = 1;
	if (keycode == KEY_S)
		input->key_s = 1;
	if (keycode == KEY_D)
		input->key_d = 1;
	if (keycode == KEY_UP)
		input->key_up = 1;
	if (keycode == KEY_LEFT)
		input->key_left = 1;
	if (keycode == KEY_DOWN)
		input->key_down = 1;
	if (keycode == KEY_RIGHT)
		input->key_right = 1;
	return (0);
}

int		on_key_release(int keycode, void *params)
{
	t_input	*input;

	input = &((t_data *) params)->input;
	if (keycode == KEY_SPACE)
		input->key_space = 0;
	if (keycode == KEY_SHIFT)
		input->key_shift = 0;
	if (keycode == KEY_W)
		input->key_w = 0;
	if (keycode == KEY_A)
		input->key_a = 0;
	if (keycode == KEY_S)
		input->key_s = 0;
	if (keycode == KEY_D)
		input->key_d = 0;
	if (keycode == KEY_UP)
		input->key_up = 0;
	if (keycode == KEY_LEFT)
		input->key_left = 0;
	if (keycode == KEY_DOWN)
		input->key_down = 0;
	if (keycode == KEY_RIGHT)
		input->key_right = 0;
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
