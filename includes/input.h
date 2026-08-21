/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:23:20 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 20:10:38 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <sys/time.h>
# include "types.h"

# define SPEED 10.0
# define SENSITIVITY 1.0

# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_SHIFT 65505
# define KEY_SPACE 32
# define KEY_Z 122

void	handle_input(t_input *input, int keycode, int down);
void	tick_input(t_data *data);

void	move(t_data *data, t_vector vec);
void	rotate_horizontal(t_data *data, double radians);
void	rotate_vertical(t_data *data, double radians);

#endif
