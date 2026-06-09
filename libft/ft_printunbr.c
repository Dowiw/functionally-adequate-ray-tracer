/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 16:43:43 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 18:17:50 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printunbrr(unsigned int n);

int	ft_printunbr(unsigned int n)
{
	if (n == 0)
		return (ft_printchar('0'));
	return (ft_printunbrr(n));
}

static int	ft_printunbrr(unsigned int n)
{
	if (n != 0)
		return (ft_printunbrr(n / 10) + ft_printchar('0' + n % 10));
	return (0);
}
