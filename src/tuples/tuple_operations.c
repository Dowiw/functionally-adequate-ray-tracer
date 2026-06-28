/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 00:44:27 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/16 14:18:48 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <unistd.h>

/**
 * @brief Add two tuples (a + b) and returns sum
 * 
 * The type of the sum is based on the type of the input tuples:
 * - POINT + POINT = INVALID_POS
 * - POINT + VECTOR = POINT
 * - VECTOR + POINT = POINT
 * - VECTOR + VECTOR = VECTOR
 * 
 * @param a tuple a
 * @param b tuple b
 * @returns the sum by value
 */
t_tuple	tuples_add(const t_tuple a, const t_tuple b)
{
	t_tuple	sum;

	sum.x = a.x + b.x;
	sum.y = a.y + b.y;
	sum.z = a.z + b.z;
	sum.w = a.w + b.w;
	return (sum);
}

/**
 * @brief Subtract two tuples (a - b) and returns difference
 * 
 * The type of the difference is based on the type of the input tuples:
 * - POINT - POINT = VECTOR
 * - POINT - VECTOR = POINT
 * - VECTOR - POINT = INVALID_NEG
 * - VECTOR - VECTOR = VECTOR
 * 
 * @param a tuple a
 * @param b tuple b
 * @returns the difference by value
 */
t_tuple	tuples_sub(const t_tuple a, const t_tuple b)
{
	t_tuple	diff;

	diff.x = a.x - b.x;
	diff.y = a.y - b.y;
	diff.z = a.z - b.z;
	diff.w = a.w - b.w;
	return (diff);
}

/**
 * @brief Negates a tuple to its opposite form
 * 
 * @param a tuple a
 * @returns negated tuple
 */
t_tuple	tuple_neg(const t_tuple a)
{
	t_tuple	neg;

	neg.x = a.x * -1.0;
	neg.y = a.y * -1.0;
	neg.z = a.z * -1.0;
	neg.w = a.w * -1.0;
	return (neg);
}

/**
 * @brief Multiplies a tuple by a scalar
 * 
 * @param a 
 * @param scalar 
 * @returns scaled tuple product
 */
t_tuple	tuple_mult(const t_tuple a, const double scalar)
{
	t_tuple	prod;

	prod.x = a.x * scalar;
	prod.y = a.y * scalar;
	prod.z = a.z * scalar;
	prod.w = a.w * scalar;
	return (prod);
}

/**
 * @brief Divides a tuple by a scalar
 * 
 * @param a 
 * @param scalar 
 * @return scaled tuple quotient
 */
t_tuple	tuple_div(const t_tuple a, const double scalar)
{
	t_tuple	quo;

	quo.x = a.x / scalar;
	quo.y = a.y / scalar;
	quo.z = a.z / scalar;
	quo.w = a.w / scalar;
	return (quo);
}
