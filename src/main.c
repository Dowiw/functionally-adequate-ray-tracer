/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 23:07:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "scene.h"
#include <stdio.h>

static int	error(char *msg);

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		return (error("Wrong arg count"));
	if (!init_scene(&scene))
		return (error("Failed to initialize scene"));
	if (!parse_scene(&scene, argv[1]))
		return (error("Failed to parse scene"));
	destroy_scene(&scene);
	return (0);
}

static int	error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (1);
}
