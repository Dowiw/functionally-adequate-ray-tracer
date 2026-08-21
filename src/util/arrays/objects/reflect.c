/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/19 20:27:36 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 20:27:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Reflect the vector passed based on the normal given
 *
 * @param v vector
 * @param n normal vector
 * @return t_vector reflected vector
 */
t_vector	reflect(t_vector v, t_vector n)
{
	t_vector	r;
	double		dot;

	dot = dot_product(v, n);
	r = tuples_sub(v, tuple_mult(tuple_mult(n, 2), dot));
	return (r);
}
