/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:42:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
# define RENDERING_H

# include "types.h"

void	render_scene(t_canvas *canvas, t_scene *scene);

void	render_init(t_iter *iter);

int		render_loop(t_data *data);

void	render_frame(t_data *data);

t_ray	ray_for_pixel(t_camera camera, int x, int y);

t_comps	prepare_computations(t_ray ray, t_intersect *hit);

t_color shade_hit(t_scene *scene, t_comps comps);

t_color	color_at(t_scene *scene, t_ray ray);

void	set_pixel(t_mlx *mlx, int x, int y, int color);

void	fill_pixel(t_mlx *mlx, int res, int x, int y, int color);

#endif
