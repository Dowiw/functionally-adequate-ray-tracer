/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:19:42 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:04:46 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minirt.h"
#include "parsing.h"
#include "util/arrays.h"

static int	parse_tuple_params(t_scene *scene, t_tuple *vec, char **params);

/*
 * Parses the given vector string 'str' in the following format:
 *   x,y,z (for example: 0.0,0.5,1.0)
 * The result is stored in the 'vec' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_tuple(t_scene *scene, t_tuple *tuple, char *str)
{
	int		result;
	char	**params;

	if (str == NULL)
		return (0);
	params = ft_split(str, ',');
	if (params == NULL)
		return (parse_error(scene, "Allocation Failure"));
	result = parse_tuple_params(scene, tuple, params);
	free_array((void **) params);
	return (result);
}

/**
 * @brief Parses x, y, and z double values into a generic tuple.
 *
 * @param params array of string parameters (x, y, z)
 * @param t pointer to the tuple to populate
 * @param line original line for error reporting
 * @return 1 on success, 0 on failure
 */
static int	parse_tuple_params(t_scene *scene, t_tuple *tuple, char **params)
{
	if (array_len((void **) params) != 3)
		return (parse_error(scene, "Expected <x>,<y>,<z>"));
	if (!parse_double(scene, &tuple->x, params[0]))
		return (parse_error(scene, "Failed to parse x component"));
	if (!parse_double(scene, &tuple->y, params[1]))
		return (parse_error(scene, "Failed to parse y component"));
	if (!parse_double(scene, &tuple->z, params[2]))
		return (parse_error(scene, "Failed to parse z component"));
	tuple->w = INVALID_NEG;
	return (1);
}
