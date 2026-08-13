/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:42:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/12 18:02:45 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "minirt.h"
# include "scene.h"

struct s_data;

typedef struct s_comps {
	double		t;
	t_object	obj;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	int			inside;
}	t_comps;

typedef struct s_iter {
	int		res;
	int		first;
	int		x;
	int		y;
	int		pixels;
}	t_iter;

void	render_scene(t_canvas *canvas, t_scene *scene);

void	render_init(t_iter *iter);

int		render_frame(struct s_data *data);

t_ray	ray_for_pixel(t_camera camera, int x, int y);

t_comps	prepare_computations(t_ray ray, t_intersection *hit);

t_color shade_hit(t_scene *scene, t_comps comps);

t_color	color_at(t_scene *scene, t_ray ray);

void	set_pixel(t_mlx *mlx, int x, int y, int color);

void	fill_pixel(t_mlx *mlx, int res, int x, int y, int color);

#endif
