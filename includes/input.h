/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 20:23:20 by sstark            #+#    #+#             */
/*   Updated: 2026/08/17 10:51:45 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include <sys/time.h>

# define SPEED 10.0
# define SENSITIVITY 1.0

struct s_data;

typedef struct s_input {
	int	key_w;
	int	key_a;
	int	key_s;
	int	key_d;
	int	key_shift;
	int	key_space;
	int	key_up;
	int	key_left;
	int	key_down;
	int	key_right;

	struct timeval last_time;
}	t_input;

void	tick_input(struct s_data *data);

#endif
