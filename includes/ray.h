/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 11:32:13 by sstark            #+#    #+#             */
/*   Updated: 2026/08/17 19:31:53 by sstark           ###   ########.fr       */
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

t_intersection	intersect_scene_and_hit(t_scene *scene, t_ray ray);
void			intersect_cone_fast(t_cone *cone, t_ray ray, t_intersection *hit);
void			intersect_cylinder_fast(t_cylinder *cylinder, t_ray ray, t_intersection *hit);
void			intersect_plane_fast(t_plane *plane, t_ray ray, t_intersection *hit);
void			intersect_sphere_fast(t_sphere *sphere, t_ray ray, t_intersection *hit);

#endif
