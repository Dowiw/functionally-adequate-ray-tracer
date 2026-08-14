/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:49:33 by sstark            #+#    #+#             */
/*   Updated: 2026/08/14 20:22:33 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>
#include "data.h"

void	tick_input(t_data *data)
{
	t_input			*input;
	struct timeval	time;
	double			delta;
	double			distance;
	double			radians;

	input = &data->input;
	gettimeofday(&time, NULL);
	delta = ((time.tv_sec - input->last_time.tv_sec) * 1000000 + time.tv_usec - input->last_time.tv_usec) / 1000000.0;
	distance = SPEED * delta;
	radians = SENSITIVITY * delta;
	if (input->key_space)
		move(data, vector(0.0, distance, 0.0));
	if (input->key_shift)
		move(data, vector(0.0, -distance, 0.0));
	if (input->key_w)
		move(data, vector(0.0, 0.0, -distance));
	if (input->key_a)
		move(data, vector(distance, 0.0, 0.0));
	if (input->key_s)
		move(data, vector(0.0, 0.0, distance));
	if (input->key_d)
		move(data, vector(-distance, 0.0, 0.0));
	if (input->key_up)
		rotate_vertical(data, radians);
	if (input->key_left)
		rotate_horizontal(data, -radians);
	if (input->key_down)
		rotate_vertical(data, -radians);
	if (input->key_right)
		rotate_horizontal(data, radians);
	input->last_time = time;
}
