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

/**
 * @brief Handles mapping keys to movement state within the input struct.
 * Flags the specific key as pressed (1) or released (0).
 *
 * @param keycode the X11 keycode pressed or released
 * @param input pointer to the input state tracking struct
 * @param set 1 for pressed, 0 for released
 * @return 1 if matched, 0 if not a movement key
 */
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

/**
 * @brief MLX hook for a key press event.
 * Captures escape to close, or updates movement tracking.
 *
 * @param keycode the pressed keycode
 * @param data pointer to the main data context
 * @return 0 on success
 */
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

/**
 * @brief MLX hook for a key release event.
 * Updates movement tracking to halt motion.
 *
 * @param keycode the released keycode
 * @param data pointer to the main data context
 * @return 0 on success
 */
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
