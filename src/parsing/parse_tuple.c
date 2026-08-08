/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tuple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:19:42 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 14:14:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minirt.h"
#include "parsing.h"
#include "util/arrays.h"

static int	parse_tuple_params(t_tuple *vec, char **params);

/*
 * Parses the given vector string 'str' in the following format:
 *   x,y,z (for example: 0.0,0.5,1.0)
 * The result is stored in the 'vec' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_tuple(t_tuple *tuple, char *str)
{
	int		result;
	char	**params;

	if (str == NULL)
		return (0);
	params = ft_split(str, ',');
	if (params == NULL)
		return (0);
	result = parse_tuple_params(tuple, params);
	free_array((void **) params);
	return (result);
}

static int	parse_tuple_params(t_tuple *tuple, char **params)
{
	if (array_len((void **) params) != 3)
		return (0);
	if (!parse_double(&tuple->x, params[0]))
		return (0);
	if (!parse_double(&tuple->y, params[1]))
		return (0);
	if (!parse_double(&tuple->z, params[2]))
		return (0);
	tuple->w = INVALID_NEG;
	return (1);
}
