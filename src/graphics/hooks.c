/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/20 22:23:13 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/20 22:24:10 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "input.h"
#include "types.h"

static void	set_movement_key(t_input *input, int keycode, int state)
{
	if (keycode == KEY_W)
		input->key_w = state;
	if (keycode == KEY_A)
		input->key_a = state;
	if (keycode == KEY_S)
		input->key_s = state;
	if (keycode == KEY_D)
		input->key_d = state;
	if (keycode == KEY_UP)
		input->key_up = state;
	if (keycode == KEY_LEFT)
		input->key_left = state;
	if (keycode == KEY_DOWN)
		input->key_down = state;
	if (keycode == KEY_RIGHT)
		input->key_right = state;
}

int	on_key_press(int keycode, void *param)
{
	t_input	*input;

	input = &((t_data *)param)->input;
	if (keycode == KEY_ESC)
		on_close(param);
	if (keycode == KEY_SPACE)
		input->key_space = 1;
	if (keycode == KEY_SHIFT)
		input->key_shift = 1;
	set_movement_key(input, keycode, 1);
	return (0);
}

int	on_key_release(int keycode, void *params)
{
	t_input	*input;

	input = &((t_data *)params)->input;
	if (keycode == KEY_SPACE)
		input->key_space = 0;
	if (keycode == KEY_SHIFT)
		input->key_shift = 0;
	set_movement_key(input, keycode, 0);
	return (0);
}
