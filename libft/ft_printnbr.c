/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 18:20:07 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 18:28:22 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printnbrr(long n);

int	ft_printnbr(int n)
{
	if (n == 0)
		return (ft_printchar('0'));
	if (n < 0)
		return (ft_printchar('-') + ft_printnbrr(-((long) n)));
	return (ft_printnbrr((long) n));
}

static int	ft_printnbrr(long n)
{
	if (n != 0)
		return (ft_printnbrr(n / 10) + ft_printchar('0' + n % 10));
	return (0);
}
