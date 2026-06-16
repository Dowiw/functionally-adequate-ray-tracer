/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 13:52:43 by sstark           ###   ########.fr       */
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

typedef struct s_sphere {
	t_pos	center;
	double	diameter;
	int		color;
}	t_sphere;

typedef struct s_plane {
	t_pos	pos;
	t_vec	vec;
	int		color;
}	t_plane;

typedef struct s_cylinder {
	t_pos	center;
	t_vec	vec;
	double	diameter;
	double	height;
	int		color;
}	t_cylinder;

typedef struct s_scene {
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;

	int			has_ambience;
	int			has_camera;
	int			has_light;
}	t_scene;

int		init_scene(t_scene *scene);

void	destroy_scene(t_scene *scene);

#endif
