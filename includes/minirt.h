/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:05:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

struct s_sphere;

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# define VECTOR 0.0
# define POINT 1.0
# define INVALID_NEG -1.0
# define INVALID_POS 2.0
# define COLOR 3.0

# define PI 3.14159265358979323846

# ifndef WIN_W
#  define WIN_W 1920
# endif

# ifndef WIN_H
#  define WIN_H 1080
# endif

/**
 * @brief Dynamic structure that represents a lot of things
 * from coordinates to colors.
 */
typedef struct s_tuple
{
	double x; // x-coordinate, red
	double y; // y-coordinate, green
	double z; // z-coordinate, blue
	double w; // type, extra value
}					t_tuple;

typedef t_tuple		t_point;

typedef t_tuple		t_vector;

typedef t_tuple		t_color;

/**
 * @brief Structure for rays.
 * Contains origin and direction.
 */
typedef struct s_ray
{
	t_point origin;     // starting point of a ray
	t_vector direction; // where it points
}					t_ray;

/**
 * @brief Structure for intersections.
 * Contains the number of intersections and the times a ray intersects
 */
typedef struct s_intersect
{
	unsigned int count; // the number of intersections
	double *times;      // the time (t) that a ray intersects an object
}					t_intersect;

/**
 * @brief
 *
 */
typedef struct s_intersection
{
	double			t;
	struct s_sphere	*obj;
}					t_intersection;

/**
 * @brief Struct that contains a list of t_intersection
 */
typedef struct s_intersections
{
	t_intersection	*list;
	unsigned int	count;
}					t_intersections;

/**
 * @brief Structure for a canvas.
 * Allocates pixels in memory (width * height).
 */
typedef struct s_canvas
{
	int width;       // width of canvas
	int height;      // height of canvas
	t_tuple *pixels; // 1D array of (width * height) representing colors
}					t_canvas;

/**
 * @brief Structure for mlx data
 */
typedef struct s_mlx
{
	void *mlx_ptr;  // pointer to mlx lib that allocates a XWindow Display
	void *win_ptr;  // pointer to window allocated
	void *img_ptr;  // pointer to image buffer
	char *img_data; // pointer to same img but as characters
	int bpp;        // bits per pixel
	int size_line;  // size of each line of pixes
	int endian;     // endian necessary for alignment
}					t_mlx;

/**
 * @brief Data structure for fdf data
 *
 * @param mlx mlx structure
 * @param ...
 */
typedef struct s_data
{
	t_mlx			mlx;
}					t_data;

/** ######################################################################### *
 *  TUPLES                                                                  # *
 *  ######################################################################### */

// tuple_compare.c

int					compare_doubles(const double a, const double b);
int					compare_tuples(const t_tuple *a, const t_tuple *b);

// tuple_constructs.c

t_point				point(double x, double y, double z);
t_vector			vector(double x, double y, double z);

// tuple_utils.c

double				calc_mag(const t_tuple a);
double				dot_product(const t_tuple a, const t_tuple b);
t_tuple				calc_norm(const t_tuple a);
t_tuple				cross_product(const t_tuple a, const t_tuple b);

// tuple_operations.c

t_tuple				tuples_add(const t_tuple a, const t_tuple b);
t_tuple				tuples_sub(const t_tuple a, const t_tuple b);
t_tuple				tuple_neg(const t_tuple a);
t_tuple				tuple_mult(const t_tuple a, const double scalar);
t_tuple				tuple_div(const t_tuple a, const double scalar);

/** ######################################################################### *
 *  COLORS                                                                  # *
 *  ######################################################################### */

t_tuple				shur_prod(const t_tuple color_a, const t_tuple color_b);
int					clamp_color(double color);

/** ######################################################################### *
 *  GRAPHICS                                                                # *
 *  ######################################################################### */

int					init_mlx_lib(t_mlx *mlx);
void				init_mlx(t_mlx *mlx);

int					canvas_create(t_canvas *canvas, int width, int height);
void				write_pixel(t_canvas *canvas, int x, int y, t_tuple color);
t_tuple				view_pixel(t_canvas *canvas, int x, int y);
char				*canvas_to_ppm(t_canvas *canvas);

/** ######################################################################### *
 *  MATRICES                                                                # *
 *  ######################################################################### */

typedef struct s_matrix2x2
{
	double			m[2][2];
}					t_matrix2x2;

typedef struct s_matrix3x3
{
	double			m[3][3];
}					t_matrix3x3;

typedef struct s_matrix4x4
{
	double			m[4][4];
}					t_matrix4x4;

t_matrix2x2			matrix2x2_identity(void);
t_matrix3x3			matrix3x3_identity(void);
t_matrix4x4			matrix4x4_identity(void);

int					matrix2x2_compare(t_matrix2x2 a, t_matrix2x2 b);
int					matrix3x3_compare(t_matrix3x3 a, t_matrix3x3 b);
int					matrix4x4_compare(t_matrix4x4 a, t_matrix4x4 b);

t_matrix2x2			matrix2x2_multiply(t_matrix2x2 a, t_matrix2x2 b);
t_matrix3x3			matrix3x3_multiply(t_matrix3x3 a, t_matrix3x3 b);
t_matrix4x4			matrix4x4_multiply(t_matrix4x4 a, t_matrix4x4 b);

t_tuple				matrix4x4_multiply_tuple(t_matrix4x4 a, t_tuple b);

t_matrix2x2			matrix2x2_transpose(t_matrix2x2 matrix);
t_matrix3x3			matrix3x3_transpose(t_matrix3x3 matrix);
t_matrix4x4			matrix4x4_transpose(t_matrix4x4 matrix);

double				matrix2x2_determinant(t_matrix2x2 matrix);
double				matrix3x3_determinant(t_matrix3x3 matrix);
double				matrix4x4_determinant(t_matrix4x4 matrix);

t_matrix2x2			matrix3x3_submatrix(t_matrix3x3 matrix, int row,
						int column);
t_matrix3x3			matrix4x4_submatrix(t_matrix4x4 matrix, int row,
						int column);

double				matrix3x3_minor(t_matrix3x3 matrix, int row, int column);
double				matrix4x4_minor(t_matrix4x4 matrix, int row, int column);

double				matrix3x3_cofactor(t_matrix3x3 matrix, int row, int column);
double				matrix4x4_cofactor(t_matrix4x4 matrix, int row, int column);

t_matrix2x2			matrix2x2_inverse(t_matrix2x2 matrix);
t_matrix3x3			matrix3x3_inverse(t_matrix3x3 matrix);
t_matrix4x4			matrix4x4_inverse(t_matrix4x4 matrix);

t_matrix4x4			matrix4x4_translation(double x, double y, double z);

t_matrix4x4			matrix4x4_scaling(double x, double y, double z);

t_matrix4x4			matrix4x4_rotation_x(double radians);
t_matrix4x4			matrix4x4_rotation_y(double radians);
t_matrix4x4			matrix4x4_rotation_z(double radians);

t_matrix4x4			matrix4x4_shearing(double *params);

/** ######################################################################### *
 *  RAYS                                                                    # *
 *  ######################################################################### */

t_point				position(t_ray ray, double time);
t_intersection		intersection(double t, struct s_sphere *obj);
t_intersections		intersections(unsigned int count, ...);
t_intersection		hit(t_intersections *intersections);
t_ray				transform(t_ray r, t_matrix4x4 m);

/** ######################################################################### *
 *  SPHERES                                                                 # *
 *  ######################################################################### */

t_vector			reflect(t_vector v, t_vector n);

#endif
