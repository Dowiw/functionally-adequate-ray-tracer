/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cones.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 13:30:00 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/17 13:30:00 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONES_H
# define CONES_H

# include "scene.h"

t_cone	**cones_create(void);
t_cone	cone_create(void);
t_cone	**cones_add(t_cone **array, t_cone *cone);
int		cones_len(t_cone **array);
void	free_cones(t_cone **array);
void	intersect_caps_cone(t_cone *cone, t_ray r, t_intersections *xs);

#endif
