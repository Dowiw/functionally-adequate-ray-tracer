/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_up.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 17:24:19 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/18 17:24:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_puthex_upcase(unsigned int n)
{
	char			buffer[16];
	int				i;
	int				out;
	unsigned int	temp;

	i = 0;
	out = 0;
	temp = 0;
	if (n == 0)
		return (ft_putchar('0'));
	while (n != 0)
	{
		temp = n % 16;
		if (temp < 10)
			buffer[i++] = temp + '0';
		else
			buffer[i++] = temp - 10 + 'A';
		n /= 16;
	}
	while (i--)
		out += ft_putchar(buffer[i]);
	return (out);
}

// int main() {
// 	#include <stdio.h>
// 	unsigned int test = 255;
// 	printf("%i\n", test % 16);

// 	int n = ft_puthex_upcase(test);
// 	printf("\nn: %i\n", n);
// 	return (0);
// }
