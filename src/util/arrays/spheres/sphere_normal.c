/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_normal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 13:08:28 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/29 13:08:28 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

/**
 * @brief Return the normalized vector of a sphere at p
 * 
 * @param s s
 * @param p point
 * @return t_vector normalized vector
 */
t_vector	normal_at(t_sphere *s, t_point p)
{
	return (calc_norm(tuples_sub(p, s->center)));
}