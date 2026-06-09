/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:29:01 by sstark            #+#    #+#             */
/*   Updated: 2025/06/17 08:02:27 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putf(char c, va_list args);

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		result;
	size_t	i;

	if (str == NULL)
		return (-1);
	va_start(args, str);
	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '%')
		{
			result += ft_printchar(str[i++]);
			continue ;
		}
		i++;
		if (str[i] == '\0')
			return (-1);
		result += ft_putf(str[i], args);
		i++;
	}
	return (result);
}

static int	ft_putf(char c, va_list args)
{
	char	*hex;
	char	*hex_up;

	hex = "0123456789abcdef";
	hex_up = "0123456789ABCDEF";
	if (c == 'c')
		return (ft_printchar((char) va_arg(args, int)));
	if (c == 's')
		return (ft_printstr(va_arg(args, char *)));
	if (c == 'p')
		return (ft_printptr(va_arg(args, void *)));
	if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(args, int)));
	if (c == 'u')
		return (ft_printunbr(va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_printunbr_base(va_arg(args, unsigned int), hex));
	if (c == 'X')
		return (ft_printunbr_base(va_arg(args, unsigned int), hex_up));
	if (c == '%')
		return (ft_printchar('%'));
	return (ft_printchar('%') + ft_printchar(c));
}

/*
#include <stdio.h>
int	main(void)
{
	char	test;

	int		result1;
	int		result2;

	result1 = ft_printf(
		"String: %s, Null String: %s, Character: %c, Percent: %%, "
		"Integer: %i, hex: %x, HEX: %X, Pointer: %p, Null: %p, "
		"Integer but d: %d, Unsigned: %u, Invalid: %y\n",
		"String", (char *) NULL, 'u', -128, -127, 463242, &test, NULL, 12345, 32462747
	);
	result2 = printf(
		"String: %s, Null String: %s, Character: %c, Percent: %%, "
		"Integer: %i, hex: %x, HEX: %X, Pointer: %p, Null: %p, "
		"Integer but d: %d, Unsigned: %u, Invalid: %y\n",
		"String", (char *) NULL, 'u', -128, -127, 463242, &test, NULL, 12345, 32462747
	);

	printf("Results: %d vs %d\n", result1, result2);

	printf("--------------\n");

	result2 = printf(NULL);
	printf("\n");
	result1 = ft_printf(NULL);
	printf("\n");

	printf("Results: %d vs %d\n", result1, result2);

	printf("--------------\n");

	result2 = printf("aaaaaaaaaaaa%", 'a');
	printf("\n");
	result1 = ft_printf("aaaaaaaaaaaa%", 'a');
	printf("\n");

	printf("Results: %d vs %d\n", result1, result2);
}
*/
