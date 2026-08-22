/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:13:32 by sstark            #+#    #+#             */
/*   Updated: 2026/08/21 17:08:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "parsing.h"

/**
 * @brief Parses a generic 3D vector from a string.
 * Validates that each component is within the [-1.0, 1.0] range.
 *
 * @param str the string containing x,y,z components
 * @param v pointer to the vector to populate
 * @param line original line for error reporting
 * @return 1 on success, 0 on failure
 */
int	parse_vector(t_scene *scene, t_vector *vector, char *str)
{
	if (!parse_tuple(scene, vector, str))
		return (0);
	vector->w = VECTOR;
	if (fabs(vector->x) > 1.0)
		return (parse_error(scene, "X component out of range"));
	if (fabs(vector->y) > 1.0)
		return (parse_error(scene, "Y component out of range"));
	if (fabs(vector->z) > 1.0)
		return (parse_error(scene, "Z component out of range"));
	return (1);
}
