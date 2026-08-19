/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:19:55 by sstark            #+#    #+#             */
/*   Updated: 2026/08/17 18:46:56 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"

# define ERROR_STACK_SIZE 10

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

	double		horizontal;
	double		vertical;

	t_matrix4x4	transform;
	t_matrix4x4	inverse;
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
	t_matrix4x4	inverse;
	t_material	material;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;
	t_vector	vec;
	t_material	material;
	t_matrix4x4	transform;
	t_matrix4x4	inverse;
}				t_plane;

typedef struct s_cylinder
{
	t_point		center;
	t_vector	vec;
	double		diameter;
	double		height;
	double		min;
	double		max;
	int			closed;
	t_material	material;
	t_matrix4x4	transform;
	t_matrix4x4	inverse;
}				t_cylinder;

typedef struct s_cone
{
	t_point		center;
	t_vector	vec;
	double		diameter;
	double		height;
	double		min;
	double		max;
	int			closed;
	t_material	material;
	t_matrix4x4	transform;
	t_matrix4x4	inverse;
}				t_cone;

/**
 * @brief Scene structure for all the positioning and stuff.
 *
 * Before adding an object using its respective add function,
 * you have to allocate it outside that function. i.e.
 *
 * ```C
 * t_scene w;
 * init_scene(&w);
 * t_sphere *s1 = malloc(sizeof(t_sphere));
 * *s1 = sphere_create();
 * w.spheres = spheres_add(w.spheres, s1)
 * ```
 */
typedef struct s_scene
{
	t_ambience	ambience;		// ambient lighting
	t_camera	camera;			// scene camera
	t_light		light;			// point light
	t_sphere	**spheres;		// allocated sphere list
	t_plane		**planes;		// allocated plane list
	t_cylinder	**cylinders;	// allocated cylinder list
	t_cone		**cones;		// allocated cone list

	int			has_ambience;
	int			has_camera;
	int			has_light;

	char		*error[ERROR_STACK_SIZE + 1];
	char		*error_line;
}				t_scene;

int				init_scene(t_scene *scene);
int				default_scene(t_scene *scene);
void			destroy_scene(t_scene *scene);

t_camera		create_camera(int width, int height, double fov);
void			init_camera(t_camera *camera);

void			set_transform(t_object *obj, t_matrix4x4 t);

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
					t_vector norm, int in_shadow);

/** ######################################################################### *
 *  SHADOWS                                                                 # *
 *  ######################################################################### */

int	is_shadowed(t_scene w, t_point p);

#endif
