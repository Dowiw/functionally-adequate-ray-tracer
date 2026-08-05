/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:00:26 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 14:45:20 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

# include "minirt.h"
# include "scene.h"

void	print_tuple(t_tuple tuple);

void	print_tuple_ln(t_tuple tuple);

void	print_matrix4x4_ln(t_matrix4x4 matrix);

void	print_material(t_material material);

void	print_sphere(t_sphere *sphere);

void	print_spheres(t_sphere **spheres);

void	print_camera(t_camera camera);

void	print_ambience(t_ambience ambience);

void	print_light(t_light light);

void	print_scene(t_scene *scene);

void	print_ray(t_ray ray);

void	print_ray_ln(t_ray ray);

void	print_intersections(t_intersection **intersections);

#endif
