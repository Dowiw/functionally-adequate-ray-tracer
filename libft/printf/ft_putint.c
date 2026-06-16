/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:39:35 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/15 15:39:36 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putint(int n)
{
	int		out;
	long	nbr;

	out = 0;
	nbr = n;
	if (nbr == -2147483648)
	{
		ft_putstr("-2147483648");
		return (11);
	}
	if (nbr < 0)
	{
		ft_putchar('-');
		out++;
		nbr *= -1;
	}
	if (nbr >= 0 && nbr <= 9)
		out += ft_putchar(nbr + '0');
	else if (nbr >= 10)
		out += ft_putint(nbr / 10) + ft_putint(nbr % 10);
	return (out);
}
