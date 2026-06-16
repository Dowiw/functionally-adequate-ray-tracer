/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 21:42:54 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "util/arrays.h"

t_cylinder	**cylinders_create(void)
{
	return ((t_cylinder **) array_create());
}

t_cylinder	**cylinders_add(t_cylinder **array, t_cylinder *cylinder)
{
	return ((t_cylinder **) array_add((void **) array, (void *) cylinder));
}

int	cylinders_len(t_cylinder **array)
{
	return (array_len((void **) array));
}

void	free_cylinders(t_cylinder **array)
{
	free_array((void **) array);
}
