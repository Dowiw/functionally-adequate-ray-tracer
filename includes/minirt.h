/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 19:30:59 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# define VECTOR 0.0
# define POINT 1.0
# define INVALID_NEG -1.0
# define INVALID_POS 2.0
# define COLOR 3.0

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
	double	x; // x-coordinate, red
	double	y; // y-coordinate, green
	double	z; // z-coordinate, blue
	double	w; // type, extra value
}	t_tuple;

/**
 * @brief Structure for a canvas.
 * Allocates pixels in memory (width * height).
 */
typedef struct s_canvas
{
	int		width; // width of canvas
	int		height; // height of canvas
	t_tuple	*pixels; // 1D array of (width * height) representing colors
}	t_canvas;

/**
 * @brief Structure for mlx data
 */
typedef struct s_mlx
{
	void	*mlx_ptr; // pointer to mlx lib that allocates a XWindow Display
	void	*win_ptr; // pointer to window allocated
	void	*img_ptr; // pointer to image buffer
	char	*img_data; // pointer to same img but as characters
	int		bpp; // bits per pixel
	int		size_line; // size of each line of pixes
	int		endian; // endian necessary for alignment
}	t_mlx;

/**
 * @brief Data structure for fdf data
 * 
 * @param mlx mlx structure
 * @param ...
 */
typedef struct s_data
{
	t_mlx		mlx;
}	t_data;

/** ######################################################################### *
 *  TUPLES                                                                  # *
 *  ######################################################################### */

// tuple_compare.c

int		compare_doubles(const double a, const double b);
int		compare_tuples(const t_tuple *a, const t_tuple *b);

// tuple_utils.c

double	calc_mag(const t_tuple a);
double	dot_product(const t_tuple a, const t_tuple b);
t_tuple	calc_norm(const t_tuple a);
t_tuple	cross_product(const t_tuple a, const t_tuple b);

// tuple_operations.c

t_tuple	tuples_add(const t_tuple a, const t_tuple b);
t_tuple	tuples_sub(const t_tuple a, const t_tuple b);
t_tuple	tuple_neg(const t_tuple a);
t_tuple	tuple_mult(const t_tuple a, const double scalar);
t_tuple	tuple_div(const t_tuple a, const double scalar);

/** ######################################################################### *
 *  COLORS                                                                  # *
 *  ######################################################################### */

t_tuple	shur_prod(const t_tuple color_a, const t_tuple color_b);

/** ######################################################################### *
 *  GRAPHICS                                                                # *
 *  ######################################################################### */

int		init_mlx_lib(t_mlx *mlx);
void	init_mlx(t_mlx *mlx);

int	canvas_create(t_canvas *canvas, int width, int height);

#endif
