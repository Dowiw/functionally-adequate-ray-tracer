/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 19:35:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>
#include <stdio.h>

typedef struct s_proj
{
	t_tuple	pos;
	t_tuple	vel;
}	t_proj;

typedef struct s_env
{
	t_tuple	grav;
	t_tuple	wind;
}	t_env;

/**
 * @brief First main function that generated the first image
 * 
 */
int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;

	t_tuple	velo = {5.0, 10.0, 0, VECTOR};
	t_proj p = { .pos = {0, 1, 0, POINT}, .vel = tuple_mult(calc_norm(velo), 5.0)};

	t_env e = { .grav = {0, -0.1, 0, VECTOR}, .wind = {-0.01, 0, 0, VECTOR}};

	t_canvas	c;
	t_tuple		pix = {1, 0.2, 0.2, COLOR};

	if (!canvas_create(&c, 175, 150))
		return 1;
	while (p.pos.y > 0)
	{
		printf("Projectile: %f, %f, %f\n", p.pos.x, p.pos.y, p.pos.z);
		printf("Projectile velocity: %f, %f, %f\n", p.vel.x, p.vel.y, p.vel.z);

		write_pixel(&c, (int)round(p.pos.x), c.height - (int)round(p.pos.y), pix);

		p.pos = tuples_add(p.pos, p.vel);
		p.vel = tuples_add(tuples_add(p.vel, e.grav), e.wind);
	}

	canvas_to_ppm(&c);
	return (0);
}
