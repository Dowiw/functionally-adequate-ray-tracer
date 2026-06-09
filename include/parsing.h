/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:09 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 22:28:53 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "scene.h"

int	parse_scene(t_scene *scene, char *file);

int	parse_ambience(t_scene *scene, char **params);

int	parse_camera(t_scene *scene, char **params);

int	parse_light(t_scene *scene, char **params);

int	parse_color(int *color, char *str);

int	parse_double(double *num, char *str);

int	parse_int(int *num, char *str);

int	parse_vec(t_vec *vec, char *str);

#endif
