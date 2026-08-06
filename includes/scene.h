/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:37:30 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

typedef struct s_material
{
	t_color		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}				t_material;

typedef struct s_ambience
{
	double		lighting;
	int			color;
}				t_ambience;

typedef struct s_camera
{
	t_point		pos;
	t_vector	orientation;
	double		fov;

	t_matrix4x4	transform;
	double		field_of_view;

	int			width;
	int			height;

	double		half_view;
	double		aspect_ratio;
	double		half_width;
	double		half_height;
	double		pixel_size;
}				t_camera;

typedef struct s_light
{
	t_point		pos;
	t_color		intensity;
}				t_light;

typedef struct s_sphere
{
	t_point		center;
	int			color;
	double		diameter;

	t_matrix4x4	transform;
	t_material	material;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;
	t_vector	vec;
	t_material	material;
}				t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	vec;
	double		diameter;
	double		height;
	t_material	material;
}				t_cylinder;

typedef struct s_scene
{
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;

	int			has_ambience;
	int			has_camera;
	int			has_light;
}				t_scene;

int				init_scene(t_scene *scene);
int				default_scene(t_scene *scene);
void			destroy_scene(t_scene *scene);

t_camera		create_camera(int width, int height, double fov);
void			init_camera(t_camera *camera);
void			finish_camera(t_camera *camera, int width, int height);

void			set_transform(t_sphere *s, t_matrix4x4 t);
t_vector		normal_at(t_sphere *s, t_point p);
t_material		material(void);

t_light			light(t_point p, t_color c);

t_color			lighting(t_material m, t_light l, t_point pos, t_vector eye,
					t_vector norm);

#endif
