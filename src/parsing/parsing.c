/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:17 by sstark            #+#    #+#             */
/*   Updated: 2026/08/18 16:49:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include "libft/libft.h"
#include "libft/get_next_line.h"
#include "parsing.h"
#include "scene.h"
#include "util/arrays.h"
#include "util/strings.h"

static int	parse_scene_line(t_scene *scene, char *line);

static int	parse_scene_fd(t_scene *scene, int fd);

// static void	finish_parsing(t_scene *scene);

static int	error(t_scene *scene, char *msg);

// TODO:
//  - enforce ranges where the subject requires
//   - partially done, still needs to be implemented for vectors

/*
 * Parses the given .rt 'file' to the 'scene' pointer.
 * Returns true if the scene was parsed correctly, false if any errors occured.
*/
int	parse_scene(t_scene *scene, char *file)
{
	int	result;
	int	fd;

	if (!init_scene(scene))
		return (error(scene, "Failed to initialize scene"));
	if (!string_endswith(file, ".rt"))
		return (error(scene, "Requires a .rt file"));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error(scene, strerror(errno)));
	result = parse_scene_fd(scene, fd);
	close(fd);
	if (!result)
		return (error(scene, "Failed to parse scene"));
	return (1);
}

static int	parse_scene_fd(t_scene *scene, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		line = string_remove_suffix(line, "\n");
		if (line == NULL)
			return (parse_error(scene, "Allocation Failure"));
		if (!parse_scene_line(scene, line))
		{
			scene->error_line = line;
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!scene->has_ambience)
		return (parse_error(scene, "Missing ambience declaration"));
	if (!scene->has_camera)
		return (parse_error(scene, "Missing camera declaration"));
	if (!scene->has_light)
		return (parse_error(scene, "Missing light declaration"));
	return (1);
}

static int	parse_scene_line(t_scene *scene, char *line)
{
	int		result;
	char	**params;
	char	*id;

	params = ft_split(line, ' ');
	if (params == NULL)
		return (parse_error(scene, "Allocation Failure"));
	id = params[0];
	if (id == NULL || id[0] == '#')
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
	else if (string_equals(id, "co"))
		result = parse_cone(scene, params);
	else
		result = parse_error(scene, "Unrecognized identifier");
	free_array((void **) params);
	return (result);
}

// TODO: what about ambience.color?
// static void	finish_parsing(t_scene *scene)
// {
// 	int	i;

// 	i = 0;
// 	while (scene->spheres[i] != NULL)
// 	{
// 		scene->spheres[i]->material.ambient = scene->ambience.lighting;
// 		i++;
// 	}
// 	i = 0;
// 	while (scene->planes[i] != NULL)
// 	{
// 		scene->planes[i]->material.ambient = scene->ambience.lighting;
// 		i++;
// 	}
// 	i = 0;
// 	while (scene->cylinders[i] != NULL)
// 	{
// 		scene->cylinders[i]->material.ambient = scene->ambience.lighting;
// 		i++;
// 	}
// }

static int	error(t_scene *scene, char *msg)
{
	int	i;

	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (scene->error_line != NULL)
	{
		ft_putstr_fd("Error at line: ", STDERR_FILENO);
		ft_putstr_fd(scene->error_line, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(scene->error_line);
		scene->error_line = NULL;
	}
	i = 0;
	while (scene->error[i] != NULL)
	{
		ft_putstr_fd(" > ", STDERR_FILENO);
		ft_putstr_fd(scene->error[i], STDERR_FILENO);
		if (scene->error[i + 1] != NULL)
			ft_putstr_fd(":", STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		i++;
	}
	ft_bzero(scene->error, ERROR_STACK_SIZE + 1);
	return (0);
}
