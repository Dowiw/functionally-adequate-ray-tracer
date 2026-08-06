/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:09 by sstark            #+#    #+#             */
/*   Updated: 2026/08/06 15:38:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "minirt.h"
# include "scene.h"

int	parse_scene(t_scene *scene, char *file);

int	parse_ambience(t_scene *scene, char **params);

int	parse_camera(t_scene *scene, char **params);

int	parse_light(t_scene *scene, char **params);

int	parse_color(int *color, char *str);

int	parse_double(double *num, char *str);

int parse_double_range(double *num, char *str, double min, double max);

int	parse_int(int *num, char *str);

int parse_int_range(int *num, char *str, int min, int max);

int	parse_point(t_point *point, char *str);

int	parse_vector(t_vector *vector, char *str);

int	parse_tuple(t_tuple *tuple, char *str);

int	parse_cylinder(t_scene *scene, char **params);

int	parse_plane(t_scene *scene, char **params);

int	parse_sphere(t_scene *scene, char **params);

#endif
