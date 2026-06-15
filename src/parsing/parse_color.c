/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:19:46 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 22:10:26 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/colors.h"

static int	parse_color_params(int *color, char **params);

/*
 * Parses the given color string 'str' in the following format:
 *   R,G,B (for example: 255,100,100)
 * The result is stored in the 'color' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_color(int *color, char *str)
{
	int		result;
	char	**params;

	if (str == NULL)
		return (0);
	params = ft_split(str, ',');
	if (params == NULL)
		return (0);
	result = parse_color_params(color, params);
	free_array((void **) params);
	return (result);
}

static int	parse_color_params(int *color, char **params)
{
	int	red;
	int	green;
	int	blue;

	if (array_len((void **) params) != 3)
		return (0);
	if (!parse_int(&red, params[0]))
		return (0);
	if (!parse_int(&green, params[1]))
		return (0);
	if (!parse_int(&blue, params[2]))
		return (0);
	*color = rgb(red, green, blue);
	return (1);
}
