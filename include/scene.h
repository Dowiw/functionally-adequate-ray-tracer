/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 20:56:48 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

typedef struct s_vec {
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef t_vec t_pos;

typedef struct s_ambience {
	double	lighting;
	int		color;
}	t_ambience;

typedef struct s_camera {
	t_pos	pos;
	t_vec	orientation;
	double	fov;
}	t_camera;

typedef struct s_light {
	t_pos	pos;
	double	brightness;
	int		color;
}	t_light;

typedef struct s_scene {
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
}	t_scene;

#endif
