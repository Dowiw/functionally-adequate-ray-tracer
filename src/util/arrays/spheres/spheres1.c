/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:43:35 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:32 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

t_sphere	**spheres_create(void)
{
	return ((t_sphere **) array_create());
}

t_sphere	**spheres_add(t_sphere **array, t_sphere *sphere)
{
	return ((t_sphere **) array_add((void **) array, (void *) sphere));
}

int	spheres_len(t_sphere **array)
{
	return (array_len((void **) array));
}

void	free_spheres(t_sphere **array)
{
	free_array((void **) array);
}
