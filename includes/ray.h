/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:32:13 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 15:30:21 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "scene.h"

t_intersection	*create_intersection(enum object_type type, void *object, double t);
t_intersection	**intersect_sphere(t_sphere *sphere, t_ray ray);
t_intersection	**intersect_scene(t_scene *scene, t_ray ray);
t_intersection	*intersect_hit(t_intersection **intersections);

#endif
