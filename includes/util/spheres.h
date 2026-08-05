/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:04:42 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 10:41:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERES_H
# define SPHERES_H

# include "scene.h"

t_sphere	sphere_create(void);

t_sphere	**spheres_create(void);

t_sphere	**spheres_add(t_sphere **array, t_sphere *sphere);

int			spheres_len(t_sphere **array);

void		free_spheres(t_sphere **array);

#endif
