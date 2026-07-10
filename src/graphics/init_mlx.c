/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/16 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include <stdlib.h>
#include <unistd.h>

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
 * @brief Extension of init_mlx_lib to put image data.
 * Frees things if NULL is returned
 */
static int	put_img_data(t_mlx *mlx, int *bpp, int *size_line, int *endian)
{
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, bpp, size_line, endian);
	if (!mlx->img_data)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		write(2, "Error: mlx_get_data_addr failed\n", 33);
		return (0);
	}
	return (1);
}

/**
 * @brief Initializes the library into the struct.
 * TODO: Also attaches the used event hooks to the window
 * NOTE: data is only for key events
 */
int	init_mlx_lib(t_mlx *mlx)
{
	init_mlx(mlx);
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_W, WIN_H, "Fils de Fer");
	if (!mlx->win_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	if (!mlx->img_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		return (0);
	}
	if (!put_img_data(mlx, &mlx->bpp, &mlx->size_line, &mlx->endian))
		return (0);
	return (1);
}
