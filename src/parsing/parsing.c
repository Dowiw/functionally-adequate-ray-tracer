/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:17 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 22:29:26 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "parsing.h"
#include "scene.h"
#include "util_arrays.h"
#include "util_strings.h"

static int	parse_line(t_scene *scene, char *line);

// TODO:
//  - terminate on parse_line error
//  - require exactly one initialization of ambience, camera and light
//  - parse objects

/*
 * Parses the given .rt 'file' to the 'scene' pointer.
 * Returns true if the scene was parsed correctly, false if any errors occured.
*/
int	parse_scene(t_scene *scene, char *file)
{
	int		fd;
	char	*line;

	if (!string_endswith(file, ".rt"))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_line(scene, line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	parse_line(t_scene *scene, char *line)
{
	int		result;
	char	**params;
	char	*id;

	params = ft_split(line, ' ');
	if (params == NULL)
		return (0);
	id = params[0];
	if (id == NULL)
		result = 1;
	else if (string_equals(id, "A"))
		result = parse_ambience(scene, params);
	else if (string_equals(id, "C"))
		result = parse_camera(scene, params);
	else if (string_equals(id, "L"))
		result = parse_light(scene, params);
	else
		result = 0;
	free_array((void **) params);
	return (result);
}
