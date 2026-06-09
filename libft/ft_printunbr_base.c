/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printunbr_base.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:15:12 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 18:26:25 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printunbrr_base(unsigned long n, char *b, size_t len);

int	ft_printunbr_base(unsigned int n, char *base)
{
	size_t	len;

	len = ft_strlen(base);
	if (len < 2)
		return (0);
	if (n == 0)
		return (ft_printchar(base[0]));
	return (ft_printunbrr_base((unsigned long) n, base, len));
}

static int	ft_printunbrr_base(unsigned long n, char *b, size_t len)
{
	if (n != 0)
		return (ft_printunbrr_base(n / len, b, len) + ft_printchar(b[n % len]));
	return (0);
}
