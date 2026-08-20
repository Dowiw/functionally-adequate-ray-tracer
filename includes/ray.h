/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:32:13 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:59:37 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "types.h"

t_intersect		*create_intersection(enum e_shape type, void *obj, double t);
t_intersects	intersect(t_object *obj, t_ray r);
t_intersects	intersect_sphere(t_sphere *sphere, t_ray ray);
t_intersects	intersect_plane(t_plane *plane, t_ray ray);
t_intersects	intersect_cylinder(t_cylinder *cylinder, t_ray ray);
t_intersects	intersect_cone(t_cone *cone, t_ray ray);
t_intersects	intersect_scene(t_scene *scene, t_ray ray);
t_intersect		*intersect_hit(t_intersects intersections);

t_intersect		intersect_scene_and_hit(t_scene *scene, t_ray ray);
void			intersect_cone_fast(t_cone *cone, t_ray ray, t_intersect *hit);
void			intersect_cylinder_fast(t_cylinder *cylinder, t_ray ray, t_intersect *hit);
void			intersect_plane_fast(t_plane *plane, t_ray ray, t_intersect *hit);
void			intersect_sphere_fast(t_sphere *sphere, t_ray ray, t_intersect *hit);

#endif
