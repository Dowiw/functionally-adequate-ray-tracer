/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_direction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/18 14:36:39 by sstark            #+#    #+#             */
/*   Updated: 2026/08/18 14:43:42 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"
#include "scene.h"

/**
 * @brief Parses a normalized direction vector from a string.
 * Validates that each component is within the [-1.0, 1.0] range.
 *
 * @param str the string containing x,y,z components
 * @param v pointer to the vector to populate
 * @param line original line for error reporting
 * @return 1 on success, 0 on failure
 */
int	parse_direction(t_scene *scene, t_vector *direction, char *str)
{
	if (!parse_vector(scene, direction, str))
		return (0);
	if (calc_mag(*direction) == 0.0)
		return (parse_error(scene, "Vector is 0"));
	return (1);
}
