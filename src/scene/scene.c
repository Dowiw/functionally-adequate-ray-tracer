/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:15:24 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:17:16 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"
#include "util/cylinders.h"
#include "util/planes.h"
#include "util/spheres.h"

int		init_scene(t_scene *scene)
{
	scene->cylinders = cylinders_create();
	scene->planes = planes_create();
	scene->spheres = spheres_create();
	return (scene->cylinders != NULL && scene->planes != NULL && scene->spheres != NULL);
}

void	destroy_scene(t_scene *scene)
{
	free_cylinders(scene->cylinders);
	free_planes(scene->planes);
	free_spheres(scene->spheres);
}
