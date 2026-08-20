/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:13:32 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:56:09 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

/**
 * @brief Parses a generic 3D vector from a string.
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
	return (1);
}
