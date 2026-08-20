/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 17:17:21 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:41:14 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# include <sys/time.h>

# ifndef ERROR_STACK_SIZE
#  define ERROR_STACK_SIZE 10
# endif

/**
 * @brief Dynamic structure that represents a lot of things
 * from coordinates to colors.
 */
typedef struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
}				t_tuple;

typedef t_tuple	t_point;
typedef t_tuple	t_vector;
typedef t_tuple	t_color;

typedef struct s_m2x2
{
	double			m[2][2];
}				t_m2x2;

typedef struct s_m3x3
{
	double			m[3][3];
}				t_m3x3;

typedef struct s_m4x4
{
	double			m[4][4];
}				t_m4x4;

/**
 * @brief Structure for rays.
 * Contains origin and direction.
 */
typedef struct s_ray
{
	t_point		origin;
	t_vector	dir;
}				t_ray;

enum	e_shape
{
	SPHERE,
	PLANE,
	CYLINDER,
	CONE
};

typedef struct s_object
{
	enum e_shape		type;
	void				*ptr;
}					t_object;

/**
 * @brief Struct for an intersection.
 */
typedef struct s_intersect
{
	double		t;
	t_object	obj;
}					t_intersect;

/**
 * @brief Struct for all intersections.
 * Contains a list of t_intersect and the amount.
 */
typedef struct s_intersects
{
	t_intersect	**list;
	int			count;
}				t_intersects;

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

	t_m4x4		transform;
	t_m4x4		inverse;
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
	t_point		pos;
	int			color;
	double		d;
	t_m4x4		transform;
	t_m4x4		inverse;
	t_material	material;
}				t_sphere;

typedef struct s_plane
{
	t_point		pos;
	t_vector	vec;
	t_material	material;
	t_m4x4		transform;
	t_m4x4		inverse;
}				t_plane;

typedef struct s_cylinder
{
	t_point		pos;
	t_vector	vec;
	double		d;
	double		height;
	double		min;
	double		max;
	int			closed;
	t_material	material;
	t_m4x4		transform;
	t_m4x4		inverse;
}				t_cylinder;

typedef struct s_cone
{
	t_point		pos;
	t_vector	vec;
	double		d;
	double		height;
	double		min;
	double		max;
	int			closed;
	t_material	material;
	t_m4x4		transform;
	t_m4x4		inverse;
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
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	t_sphere	**spheres;
	t_plane		**planes;
	t_cylinder	**cylinders;
	t_cone		**cones;

	int			has_ambience;
	int			has_camera;
	int			has_light;

	char		*error[ERROR_STACK_SIZE + 1];
	char		*error_line;
}				t_scene;

/**
 * @brief Structure for a canvas.
 * Allocates pixels in memory (width * height).
 */
typedef struct s_canvas
{
	int		width;
	int		height;
	t_tuple	*pixels;
}				t_canvas;

/**
 * @brief Structure for mlx data
 */
typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_data;
	int		bpp;
	int		size_line;
	int		endian;
}				t_mlx;

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

typedef struct s_input {
	int				key_w;
	int				key_a;
	int				key_s;
	int				key_d;
	int				key_shift;
	int				key_space;
	int				key_up;
	int				key_left;
	int				key_down;
	int				key_right;

	struct timeval	last_time;
}	t_input;

typedef struct s_data
{
	t_scene	scene;
	t_mlx	mlx;
	t_iter	iter;
	t_input	input;
}				t_data;

#endif
