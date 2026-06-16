/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:43:23 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

t_plane	**planes_create(void)
{
	return ((t_plane **) array_create());
}

t_plane	**planes_add(t_plane **array, t_plane *plane)
{
	return ((t_plane **) array_add((void **) array, (void *) plane));
}

int	planes_len(t_plane **array)
{
	return (array_len((void **) array));
}

void	free_planes(t_plane **array)
{
	free_array((void **) array);
}
