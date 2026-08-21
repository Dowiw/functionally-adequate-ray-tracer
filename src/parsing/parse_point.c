/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:12:08 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:49:24 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

/**
 * @brief Parses a 3D point (coordinate) from a string.
 *
 * @param str the string containing x,y,z components
 * @param p pointer to the point to populate
 * @param line original line for error reporting
 * @return 1 on success, 0 on failure
 */
int	parse_point(t_scene *scene, t_point *point, char *str)
{
	if (!parse_tuple(scene, point, str))
		return (0);
	point->w = POINT;
	return (1);
}
