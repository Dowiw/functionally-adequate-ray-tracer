/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:19:42 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:09:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"

static int	parse_vec_params(t_vec *vec, char **params);

/*
 * Parses the given vector string 'str' in the following format:
 *   x,y,z (for example: 0.0,0.5,1.0)
 * The result is stored in the 'vec' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_vec(t_vec *vec, char *str)
{
	int		result;
	char	**params;

	if (str == NULL)
		return (0);
	params = ft_split(str, ',');
	if (params == NULL)
		return (0);
	result = parse_vec_params(vec, params);
	free_array((void **) params);
	return (result);
}

static int	parse_vec_params(t_vec *vec, char **params)
{
	if (array_len((void **) params) != 3)
		return (0);
	if (!parse_double(&vec->x, params[0]))
		return (0);
	if (!parse_double(&vec->y, params[1]))
		return (0);
	if (!parse_double(&vec->z, params[2]))
		return (0);
	return (1);
}
