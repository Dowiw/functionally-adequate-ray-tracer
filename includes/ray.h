/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:32:13 by sstark            #+#    #+#             */
/*   Updated: 2026/08/10 17:05:39 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "minirt.h"
# include "scene.h"

t_intersection	*create_intersection(enum e_object_type type, void *object, double t);
t_intersections	intersect(t_object *obj, t_ray r);
t_intersections	intersect_sphere(t_sphere *sphere, t_ray ray);
t_intersections	intersect_plane(t_plane *plane, t_ray ray);
t_intersections	intersect_cylinder(t_cylinder *cylinder, t_ray ray);
t_intersections	intersect_cone(t_cone *cone, t_ray ray);
t_intersections	intersect_scene(t_scene *scene, t_ray ray);
t_intersection	*intersect_hit(t_intersections intersections);

#endif
