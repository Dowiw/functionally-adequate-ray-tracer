/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:35:05 by sstark            #+#    #+#             */
/*   Updated: 2026/08/12 14:11:15 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "data.h"
#include "libft/libft.h"
#include "parsing.h"
#include "rendering.h"
#include "scene.h"

static int	error(char *msg);

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (error("Wrong arg count"));
	if (!parse_scene(&data.scene, argv[1]))
	{
		destroy_scene(&data.scene);
		return (0);
	}
	if (!init_mlx_lib(&data.mlx, &data))
	{
		destroy_scene(&data.scene);
		destroy_mlx(&data.mlx);
		return (error("Failed to initialize mlx"));
	}
	render_init(&data.iter);
	mlx_loop(data.mlx.mlx_ptr);
	destroy_scene(&data.scene);
	destroy_mlx(&data.mlx);
	return (0);
}

static int	error(char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}
