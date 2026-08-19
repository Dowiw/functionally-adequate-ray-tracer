/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "types.h"

int				init_scene(t_scene *scene);
int				default_scene(t_scene *scene);
void			destroy_scene(t_scene *scene);

t_camera		create_camera(int width, int height, double fov);
void			init_camera(t_camera *camera);

void			set_transform(t_object *obj, t_m4x4 t);

/** ######################################################################### *
 *  SPHERES                                                                 # *
 *  ######################################################################### */

t_vector		normal_at(t_object *obj, t_point p);
t_material		material(void);

/** ######################################################################### *
 *  LIGHTING                                                                # *
 *  ######################################################################### */

t_light			light(t_point p, t_color c);
t_color			lighting(t_material m, t_light l, t_point pos, t_vector eye,
					t_vector norm, int in_shadow, t_ambience g);

/** ######################################################################### *
 *  SHADOWS                                                                 # *
 *  ######################################################################### */

int	is_shadowed(t_scene w, t_point p);

#endif
