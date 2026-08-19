/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_transform.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:49:14 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:06 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_m4x4 view_orientation(t_tuple forward, t_tuple up, t_tuple left);

/**
 * @brief Returns the view transformation matrix for the camera.
 * The cameras origin is at 'from', looking towards 'to',
 * with 'up' specifying the cameras tilt.
 *
 * @param from
 * @param to
 * @param up
 * @return t_m4x4
 */
t_m4x4	view_transform(t_point from, t_point to, t_vector up)
{
	t_tuple		forward;
	t_tuple		left;
	t_tuple		true_up;

	forward = calc_norm(tuples_sub(to, from));
	left = cross_product(forward, calc_norm(up));
	true_up = cross_product(left, forward);
	return (m4x4_multiply(view_orientation(forward, true_up, left), m4x4_translation(-from.x, -from.y, -from.z)));
}

static t_m4x4 view_orientation(t_tuple forward, t_tuple up, t_tuple left)
{
	t_m4x4	result;

	result.m[0][0] = left.x;
	result.m[0][1] = left.y;
	result.m[0][2] = left.z;
	result.m[0][3] = 0.0;
	result.m[1][0] = up.x;
	result.m[1][1] = up.y;
	result.m[1][2] = up.z;
	result.m[1][3] = 0.0;
	result.m[2][0] = -forward.x;
	result.m[2][1] = -forward.y;
	result.m[2][2] = -forward.z;
	result.m[2][3] = 0.0;
	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return (result);
}
