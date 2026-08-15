/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 13:40:31 by sstark            #+#    #+#             */
/*   Updated: 2026/08/14 19:44:54 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_H
# define DATA_H

# include "input.h"
# include "minirt.h"
# include "parsing.h"
# include "rendering.h"

/**
 * @brief Data structure for all data passed to mlx loop
 */
typedef struct s_data
{
	t_scene 	scene;
	t_mlx		mlx;
	t_iter		iter;
	t_input		input;
}				t_data;

#endif
