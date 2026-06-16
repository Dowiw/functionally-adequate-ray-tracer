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

int main(int argc, char **argv, char **envp) {
	(void)argc;
	(void)argv;
	(void)envp;

	t_tuple	velo = {60, 20, 0, VECTOR};
	t_proj p = { .pos = {0, 1, 0, POINT}, .vel = calc_norm(velo)};
	t_env e = { .grav = {0, -0.1, 0, VECTOR}, .wind = {-0.01, 0, 0, VECTOR}};

	while (p.pos.y > 0)
	{
		printf("Projectile: %f, %f, %f\n", p.pos.x, p.pos.y, p.pos.z);
		printf("Projectile velocity: %f, %f, %f\n", p.vel.x, p.vel.y, p.vel.z);
		p.pos = tuples_add(p.pos, p.vel);
		p.vel = tuples_add(tuples_add(p.vel, e.grav), e.wind);
	}

	return (0);
}
