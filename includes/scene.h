/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:02:37 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "types.h"

int			init_scene(t_scene *scene);
void		destroy_scene(t_scene *scene);

t_camera	create_camera(int width, int height, double fov);
void		init_camera(t_camera *camera);

void		set_transform(t_object *obj, t_m4x4 t);

t_vector	normal_at(t_object *obj, t_point p);
t_material	material(void);

t_light		light(t_point p, t_color c);
t_color		lighting(t_material m, t_scene s, t_comps comps, int in_shadow);

int			is_shadowed(t_scene w, t_point p);

#endif
