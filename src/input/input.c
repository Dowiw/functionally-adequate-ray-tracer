/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/14 19:49:33 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 20:15:00 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <sys/time.h>
#include "input.h"
#include "minirt.h"
#include "types.h"

static void	process_input(t_data *data, double distance, double radians);

/**
 * @brief Resets the progressive render iteration state if any movement occurred.
 * Ensures that camera changes immediately restart the render.
 *
 * @param data pointer to the main context
 * @return 1 if movement occurred, 0 otherwise
 */
void	handle_input(t_input *input, int keycode, int down)
{
	if (keycode == KEY_SPACE)
		input->key_space = down;
	if (keycode == KEY_SHIFT)
		input->key_shift = down;
	if (keycode == KEY_W)
		input->key_w = down;
	if (keycode == KEY_A)
		input->key_a = down;
	if (keycode == KEY_S)
		input->key_s = down;
	if (keycode == KEY_D)
		input->key_d = down;
	if (keycode == KEY_UP)
		input->key_up = down;
	if (keycode == KEY_LEFT)
		input->key_left = down;
	if (keycode == KEY_DOWN)
		input->key_down = down;
	if (keycode == KEY_RIGHT)
		input->key_right = down;
}

/**
 * @brief Measures elapsed time and updates camera controls per frame.
 *
 * @param data pointer to the main context
 * @return 1 if movement triggered an update, 0 otherwise
 */
void	tick_input(t_data *data)
{
	t_input			*input;
	struct timeval	time;
	long			usecs;
	double			delta;

	input = &data->input;
	gettimeofday(&time, NULL);
	if (input->last_time.tv_sec == 0)
	{
		input->last_time = time;
		return ;
	}
	usecs = (time.tv_sec - input->last_time.tv_sec) * 1000000;
	usecs += time.tv_usec - input->last_time.tv_usec;
	delta = usecs / 1000000.0;
	process_input(data, SPEED * delta, SENSITIVITY * delta);
	input->last_time = time;
}

/**
 * @brief Processes continuous input states to execute movement each frame.
 *
 * @param data pointer to the main context
 * @param dt delta time
 */
static void	process_input(t_data *data, double distance, double radians)
{
	if (data->input.key_space)
		move(data, vector(0.0, distance, 0.0));
	if (data->input.key_shift)
		move(data, vector(0.0, -distance, 0.0));
	if (data->input.key_w)
		move(data, vector(0.0, 0.0, -distance));
	if (data->input.key_a)
		move(data, vector(distance, 0.0, 0.0));
	if (data->input.key_s)
		move(data, vector(0.0, 0.0, distance));
	if (data->input.key_d)
		move(data, vector(-distance, 0.0, 0.0));
	if (data->input.key_up)
		rotate_vertical(data, radians);
	if (data->input.key_left)
		rotate_horizontal(data, -radians);
	if (data->input.key_down)
		rotate_vertical(data, -radians);
	if (data->input.key_right)
		rotate_horizontal(data, radians);
}
