/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 17:28:18 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 17:34:00 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "types.h"

# ifndef WIN_W
#  define WIN_W 960
# endif

# ifndef WIN_H
#  define WIN_H 540
# endif

int		init_mlx_lib(t_mlx *mlx, t_data *data);
void	init_mlx(t_mlx *mlx);
int		on_key_press(int keycode, void *param);
int		on_key_release(int keycode, void *param);
int		on_close(void *param);
int		destroy_mlx(t_mlx *mlx);

int		canvas_create(t_canvas *canvas, int width, int height);
void	write_pixel(t_canvas *canvas, int x, int y, t_tuple color);
t_tuple	view_pixel(t_canvas *canvas, int x, int y);
char	*canvas_to_ppm(t_canvas *canvas);

#endif
