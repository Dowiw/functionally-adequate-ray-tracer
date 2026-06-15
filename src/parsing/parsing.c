/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:17 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 23:29:20 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../libft/libft.h"
#include "../libft/get_next_line.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/strings.h"

static int	parse_line(t_scene *scene, char *line);

// TODO:
//  - require exactly one initialization of ambience, camera and light
//  - enforce ranges where the subject requires
//  - probably a good idea to handle over-/underflow
//  - consider moving error printing down the parsing chain to get more details

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
		line = string_remove_suffix(line, "\n");
		if (!parse_line(scene, line))
		{
			free(line);
			close(fd);
			return (0);
		}
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
	result = 0;
	id = params[0];
	if (id == NULL)
		result = 1;
	else if (string_equals(id, "A"))
		result = parse_ambience(scene, params);
	else if (string_equals(id, "C"))
		result = parse_camera(scene, params);
	else if (string_equals(id, "L"))
		result = parse_light(scene, params);
	else if (string_equals(id, "sp"))
		result = parse_sphere(scene, params);
	else if (string_equals(id, "pl"))
		result = parse_plane(scene, params);
	else if (string_equals(id, "cy"))
		result = parse_cylinder(scene, params);
	free_array((void **) params);
	return (result);
}
