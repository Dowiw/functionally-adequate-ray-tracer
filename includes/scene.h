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

# include "minirt.h"

typedef struct s_ambience {
	double	lighting;
	int		color;
}	t_ambience;

typedef struct s_camera {
	t_point		pos;
	t_vector	orientation;
	double		fov;
}	t_camera;

typedef struct s_light {
	t_point	pos;
	double	brightness;
	int		color;
}	t_light;

typedef struct s_sphere {
	t_point		center;
	t_matrix4x4	transform;
	double		radius;
	double		diameter;
	int			color;
}	t_sphere;

typedef struct s_plane {
	t_point	pos;
	t_vector	vec;
	int		color;
}	t_plane;

typedef struct s_cylinder {
	t_point	center;
	t_vector	vec;
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

t_intersections	intersect(t_sphere *s, t_ray r);
void			set_transform(t_sphere *s, t_matrix4x4 t);

#endif
