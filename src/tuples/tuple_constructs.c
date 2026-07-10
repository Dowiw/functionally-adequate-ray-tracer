/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_constructs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:14:02 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/29 13:17:26 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Point constructor
 * 
 * @param x x
 * @param y y
 * @param z z
 * @return t_point point
 */
t_point	point(double x, double y, double z)
{
	t_point	p;

	p.x = x;
	p.y = y;
	p.z = z;
	p.w = POINT;
	return (p);
}

/**
 * @brief Vector constructor
 * 
 * @param x x
 * @param y y
 * @param z z
 * @return t_vector vector
 */
t_vector	vector(double x, double y, double z)
{
	t_vector	v;

	v.x = x;
	v.y = y;
	v.z = z;
	v.w = VECTOR;
	return (v);
}
