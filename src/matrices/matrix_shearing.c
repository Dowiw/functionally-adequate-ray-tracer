/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_shearing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 13:00:38 by sstark            #+#    #+#             */
/*   Updated: 2026/06/19 13:04:39 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix4x4	matrix4x4_shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
	return ((t_matrix4x4){{
		{1.0, xy, xz, 0.0},
		{yx, 1.0, yz, 0.0},
		{zx, zy, 1.0, 0.0},
		{0.0, 0.0, 0.0, 1.0}
	}});
}
