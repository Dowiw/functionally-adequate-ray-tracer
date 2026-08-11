/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/08/11 12:50:51 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"
#include "libft/libft.h"
#include "parsing.h"
#include "rendering.h"
#include "scene.h"

static int	error(char *msg);

int	main(int argc, char **argv)
{
	t_scene		scene;
	t_canvas	canvas;

	if (argc != 2)
		return (error("Wrong arg count"));
	if (!init_scene(&scene))
		return (error("Failed to initialize scene"));
	if (!parse_scene(&scene, argv[1]))
		return (0);
	if (!canvas_create(&canvas, scene.camera.width, scene.camera.height))
	{
		destroy_scene(&scene);
		return (error("Failed to create canvas"));
	}
	print_scene(&scene);
	render_scene(&canvas, &scene);
	canvas_to_ppm(&canvas);
	destroy_scene(&scene);
	return (0);
}

static int	error(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
