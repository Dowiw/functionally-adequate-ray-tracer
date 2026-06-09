/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printptr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 15:19:34 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 18:41:57 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printptrr(unsigned long ptr);

int	ft_printptr(void *ptr)
{
	if (ptr == NULL)
		return (ft_printstr("(nil)"));
	return (ft_printstr("0x") + ft_printptrr((unsigned long) ptr));
}

static int	ft_printptrr(unsigned long ptr)
{
	char	*hex;

	hex = "0123456789abcdef";
	if (ptr != 0)
		return (ft_printptrr(ptr / 16) + ft_printchar(hex[ptr % 16]));
	return (0);
}
