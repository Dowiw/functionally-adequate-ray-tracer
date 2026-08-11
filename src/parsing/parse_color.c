/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:19:46 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:34:45 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parsing.h"
#include "util/arrays.h"
#include "util/colors.h"

static int	parse_color_params(t_scene *scene, int *color, char **params);

/*
 * Parses the given color string 'str' in the following format:
 *   R,G,B (for example: 255,100,100)
 * The result is stored in the 'color' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_color(t_scene *scene, int *color, char *str)
{
	int		result;
	char	**params;

	if (str == NULL)
		return (0);
	params = ft_split(str, ',');
	if (params == NULL)
		return (parse_error(scene, "Allocation Failure"));
	result = parse_color_params(scene, color, params);
	free_array((void **) params);
	return (result);
}

static int	parse_color_params(t_scene *scene, int *color, char **params)
{
	int	red;
	int	green;
	int	blue;

	if (array_len((void **) params) != 3)
		return (parse_error(scene, "Bad format, expected <red>,<green>,<blue>"));
	if (!parse_int_range(scene, &red, params[0], 0, 255))
		return (parse_error(scene, "Failed to parse red component"));
	if (!parse_int_range(scene, &green, params[1], 0, 255))
		return (parse_error(scene, "Failed to parse green component"));
	if (!parse_int_range(scene, &blue, params[2], 0, 255))
		return (parse_error(scene, "Failed to parse blue component"));
	*color = rgb(red, green, blue);
	return (1);
}
