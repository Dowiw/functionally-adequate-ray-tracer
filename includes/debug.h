/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:00:26 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:20:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include <stdio.h>
# include "minirt.h"
# include "rendering.h"
# include "scene.h"

void	print_tuple(t_tuple tuple);

void	print_tuple_ln(t_tuple tuple);

void	print_m4x4_ln(t_m4x4 matrix);

void	print_material(t_material material);

void	print_sphere(t_sphere *sphere);

void	print_spheres(t_sphere **spheres);

void	print_camera(t_camera camera);

void	print_ambience(t_ambience ambience);

void	print_light(t_light light);

void	print_scene(t_scene *scene);

void	print_ray(t_ray ray);

void	print_ray_ln(t_ray ray);

void	print_intersects(t_intersect **intersections);

void	print_comps(t_comps comps);

#endif
