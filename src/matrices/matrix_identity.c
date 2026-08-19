/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_identity.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/19 08:57:56 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:13:23 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m2x2	m2x2_identity(void)
{
	t_m2x2	result;

	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	return (result);
}

t_m3x3	m3x3_identity(void)
{
	t_m3x3	result;

	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	result.m[1][2] = 0.0;
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 1.0;
	return (result);
}

t_m4x4	m4x4_identity(void)
{
	t_m4x4	result;

	result.m[0][0] = 1.0;
	result.m[0][1] = 0.0;
	result.m[0][2] = 0.0;
	result.m[0][3] = 0.0;
	result.m[1][0] = 0.0;
	result.m[1][1] = 1.0;
	result.m[1][2] = 0.0;
	result.m[1][3] = 0.0;
	result.m[2][0] = 0.0;
	result.m[2][1] = 0.0;
	result.m[2][2] = 1.0;
	result.m[2][3] = 0.0;
	result.m[3][0] = 0.0;
	result.m[3][1] = 0.0;
	result.m[3][2] = 0.0;
	result.m[3][3] = 1.0;
	return (result);
}
