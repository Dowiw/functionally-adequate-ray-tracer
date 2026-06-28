/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 23:07:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_int.h"
#include "scene.h"
#include "util/spheres.h"
#include <X11/Xlib.h>

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;

	int		canvas_pixels = 100;
	t_canvas	c;
	double		wall_size = 7.0;
	double		wall_z = 10.0;

	double		pixel_size = wall_size / (double)canvas_pixels;
	double		half = wall_size / 2;

	if (!canvas_create(&c, canvas_pixels, canvas_pixels))
		return 1;
	t_color		clr = {1, 0, 0, COLOR};
	t_sphere	s = sphere_create();

	t_point	ray_origin = {0, 0, -5, POINT};
	t_ray	r;
	double	world_y = 0;
	double	world_x = 0;
	t_point	pos;

	t_intersections	xS;
	for (int y = 0; y < canvas_pixels - 1; y++)
	{
		world_y = half - pixel_size * (double)y;
		for (int x = 0; x < canvas_pixels - 1; x++)
		{
			world_x = -(half) + pixel_size * (double)x;
			pos.x = world_x;
			pos.y = world_y;
			pos.z = wall_z;
			pos.w = POINT;

			r.origin = ray_origin;
			r.direction = calc_norm(tuples_sub(pos, ray_origin));

			xS = intersect(&s, r);
			if (hit(&xS).obj != NULL && hit(&xS).t)
				write_pixel(&c, x, y, clr);
		}
	}
	canvas_to_ppm(&c);
	return (0);
}

