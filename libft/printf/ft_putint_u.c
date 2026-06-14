/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:50:14 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/15 18:50:15 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putint_u(unsigned int n)
{
	int	out;

	out = 0;
	if (n >= 10)
		out += ft_putint_u(n / 10);
	out += ft_putchar((n % 10) + '0');
	return (out);
}
