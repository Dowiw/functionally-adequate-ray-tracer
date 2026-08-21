/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/09 16:49:41 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 19:12:15 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "scene.h"

/**
 * @brief Pushes a parsing error message onto the scene's error stack.
 *
 * @param scene scene structure containing the error stack
 * @param msg error message to push
 * @return 0 indicating failure
 */
int	parse_error(t_scene *scene, char *error)
{
	unsigned int	size_to_move;

	size_to_move = (ERROR_STACK_SIZE - 1) * sizeof(char *);
	ft_memmove(scene->error + 1, scene->error, size_to_move);
	scene->error[0] = error;
	return (0);
}
