/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   planes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:03:58 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 10:41:35 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANES_H
# define PLANES_H

# include "scene.h"

t_plane	**planes_create(void);

t_plane	plane_create(void);

t_plane	**planes_add(t_plane **array, t_plane *plane);

int		planes_len(t_plane **array);

void	free_planes(t_plane **array);

#endif
