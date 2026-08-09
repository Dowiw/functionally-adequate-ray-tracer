/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:49:41 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 17:18:36 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "scene.h"

int	parse_error(t_scene *scene, char *error)
{
	ft_memmove(scene->error + 1, scene->error, (ERROR_STACK_SIZE - 1) * sizeof(char *));
	scene->error[0] = error;
	return (0);
}
