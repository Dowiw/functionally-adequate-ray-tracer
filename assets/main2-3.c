/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2-3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx_int.h"
#include "scene.h"
#include "util/spheres.h"
#include <X11/Xlib.h>

/**
 * @brief Ray-casting a sphere silhouette onto a canvas.
 *
 * This program casts rays from a viewpoint toward a virtual wall and checks
 * if they intersect a unit sphere at the origin.
 *
 * 1. Sphere Setup:
 *    - The sphere is a unit sphere (radius = 1) centered at the origin (0, 0, 0).
 *    - ok so we know where to point.
 *
 * 2. Ray Origin / Camera:
 *    - Located at (0, 0, -5). Moving this closer makes the sphere look larger;
 *      moving it farther away makes it smaller. (i.e. changing z value)
 *
 * 3. Virtual Wall:
 *    - Placed at z = 10.0 (behind the sphere).
 *    - The size of the wall is 7.0 units. With the sphere at the origin, a size
 *      of at least 6.0 is needed to capture the shadow of the unit sphere. 7.0
 *      gives a nice margin.
 *    - Why? Ok, in order to capture the whole circle we must have all the edges in the wall.
 * If the circle is at 0, 0, 0 then 5 plus that in the z direction gives us the radius times two.
 * 5 more in the z direction and we get to the radius times three. This means that to capture one
 * half of the circle we need at least a wall bigger that 2 if we put the wall z in 5, or 3 if we
 * put the wall z in 10.
 * However, that is only one side of the circle, we must also do the same which is why we use 7.0
 * 3.0 + 3.0 + (some margin) 1.0 = 7.0 for a wall at z 10.0
 * This wall acts as the capturer of the shadow of the circle
 *
 * 4. Coordinate Mapping (Canvas -> World):
 *    - Canvas size is 100x100 pixels.
 *    - `pixel_size = wall_size / canvas_pixels` (0.07 units per pixel).
 *    - `half = wall_size / 2` (3.5 units).
 *    - For each pixel (x, y) on the canvas:
 *      - `world_x = -half + pixel_size * x`
 *      - `world_y = half - pixel_size * y`
 *
 *      Note: In world space, y increases as you go up. On the canvas, y increases
 *      as you go down. We subtract the y-offset from `half` to flip the coordinate
 *      system so the top of the canvas maps to the top of the world.
 *
 * 5. Ray Casting & Hits:
 *    - A ray is cast from `ray_origin` to the point `(world_x, world_y, wall_z)`.
 *    - Direction is normalized.
 *    - If the ray hits the sphere (`hit().obj != NULL`), we write a red pixel.
 */
int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;

	int		canvas_pixels = 100;
	t_canvas	c;
	double		wall_size = 5.0;
	double		wall_z = 5.0;

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

	t_intersects	xS;
	for (int y = 0; y < canvas_pixels; y++)
	{
		world_y = half - pixel_size * (double)y;
		for (int x = 0; x < canvas_pixels; x++)
		{
			world_x = -(half) + pixel_size * (double)x;
			pos.x = world_x;
			pos.y = world_y;
			pos.z = wall_z;
			pos.w = POINT;

			r.origin = ray_origin;
			r.dir = calc_norm(tuples_sub(pos, ray_origin));

			xS = intersect(&s, r);
			if (hit(&xS).obj != NULL && hit(&xS).t)
				write_pixel(&c, x, y, clr);
		}
	}
	canvas_to_ppm(&c);
	return (0);
}

