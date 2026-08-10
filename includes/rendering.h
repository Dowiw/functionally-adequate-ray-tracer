/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 09:42:38 by sstark            #+#    #+#             */
/*   Updated: 2026/08/10 17:05:39 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "minirt.h"
# include "scene.h"

typedef struct s_comps {
	double		t;
	t_object	obj;
	t_point		point;
	t_point		over_point;
	t_vector	eyev;
	t_vector	normalv;
	int			inside;
}	t_comps;

void	render_scene(t_canvas *canvas, t_scene *scene);

t_ray	ray_for_pixel(t_camera camera, int x, int y);

t_comps	prepare_computations(t_ray ray, t_intersection *hit);

t_color shade_hit(t_scene *scene, t_comps comps);

t_color	color_at(t_scene *scene, t_ray ray);

#endif
