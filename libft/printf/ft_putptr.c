/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:43:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/15 15:43:37 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// helper function to print out hex format of %lu
static int	ft_puthex_long(unsigned long hex)
{
	char			write_out[16];
	int				out;
	size_t			i;
	unsigned long	temp;

	out = 0;
	i = 0;
	while (hex != 0)
	{
		temp = hex % 16;
		if (temp < 10)
			write_out[i++] = temp + '0';
		else
			write_out[i++] = temp - 10 + 'a';
		hex /= 16;
	}
	while (i--)
		out += ft_putchar(write_out[i]);
	return (out);
}

int	ft_putptr(void *p)
{
	int				out;
	unsigned long	hex;

	out = 0;
	hex = (unsigned long)p;
	if (hex == 0)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	out += ft_putstr("0x");
	out += ft_puthex_long(hex);
	return (out);
}

// int main()
// {
// 	#include <stdio.h>
// 	void *hi;
// 	int n = ft_putptr(hi);
// 	printf("\nn: %i\nptr: %p\n", n, hi);
// }
