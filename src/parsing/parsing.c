/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:17 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:23:38 by sstark           ###   ########.fr       */
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

static int	parse_scene_fd(t_scene *scene, int fd);

static int	parse_scene_line(t_scene *scene, char *line);

static int	parse_scene_params(t_scene *scene, char **params);

static int	error(t_scene *scene, char *msg);

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

/**
 * @brief Reads and parses a scene file descriptor line by line.
 *
 * @param scene pointer to the scene to populate
 * @param fd open file descriptor
 * @return 1 on success, 0 on failure
 */
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
			get_next_line(-1);
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

/**
 * @brief Parses a single line from the scene description file.
 *
 * @param scene pointer to the scene to populate
 * @param line raw string line
 * @return 1 on success, 0 on failure
 */
static int	parse_scene_line(t_scene *scene, char *line)
{
	int		result;
	char	**params;

	params = ft_split(line, ' ');
	if (params == NULL)
		return (parse_error(scene, "Allocation Failure"));
	result = parse_scene_params(scene, params);
	free_array((void **) params);
	return (result);
}

/**
 * @brief Dispatches the parsed tokens of a line to the appropriate parser.
 *
 * @param scene pointer to the scene
 * @param params array of string tokens from the line
 * @param line original line string for error tracking
 * @return 1 on success, 0 on failure
 */
static int	parse_scene_params(t_scene *scene, char **params)
{
	char	*id;

	id = params[0];
	if (id == NULL || id[0] == '#')
		return (1);
	if (string_equals(id, "A"))
		return (parse_ambience(scene, params));
	if (string_equals(id, "C"))
		return (parse_camera(scene, params));
	if (string_equals(id, "L"))
		return (parse_light(scene, params));
	if (string_equals(id, "sp"))
		return (parse_sphere(scene, params));
	if (string_equals(id, "pl"))
		return (parse_plane(scene, params));
	if (string_equals(id, "cy"))
		return (parse_cylinder(scene, params));
	if (string_equals(id, "co"))
		return (parse_cone(scene, params));
	return (parse_error(scene, "Unrecognized identifier"));
}

/**
 * @brief Logs an error message to standard error during parsing.
 *
 * @param scene pointer to the scene for logging
 * @param msg error message to display
 * @return 0 indicating failure
 */
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
