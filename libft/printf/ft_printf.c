/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:47:12 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/15 14:56:17 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

// helper function to handle formatting
static int	ft_fmt_handler(const char *s, va_list *args, int i)
{
	int	out;

	out = 0;
	if (s[i + 1] == 'c')
		out += ft_putchar(va_arg(*args, int));
	else if (s[i + 1] == 's')
		out += ft_putstr(va_arg(*args, char *));
	else if (s[i + 1] == 'd' || s[i + 1] == 'i')
		out += ft_putint(va_arg(*args, int));
	else if (s[i + 1] == 'p')
		out += ft_putptr(va_arg(*args, void *));
	else if (s[i + 1] == 'u')
		out += ft_putint_u(va_arg(*args, unsigned int));
	else if (s[i + 1] == 'x')
		out += ft_puthex_lowcase(va_arg(*args, unsigned int));
	else if (s[i + 1] == 'X')
		out += ft_puthex_upcase(va_arg(*args, unsigned int));
	else if (s[i + 1] == '%')
		out += ft_putchar('%');
	return (out);
}

static int	ft_is_valid_specifier(const char *s, size_t i)
{
	return (
		s[i] == 'c' || s[i] == 's' || s[i] == 'p'
		|| s[i] == 'd' || s[i] == 'i' || s[i] == 'u'
		|| s[i] == 'x' || s[i] == 'X' || s[i] == '%'
	);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	size_t	i;
	va_list	args;

	if (!s)
		return (-1);
	i = 0;
	count = 0;
	va_start(args, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%' && s[i + 1] != '\0' && ft_is_valid_specifier(s, i + 1))
		{
			count += ft_fmt_handler(s, &args, i);
			i += 2;
		}
		else
		{
			count += ft_putchar(s[i]);
			i++;
		}
	}
	va_end(args);
	return (count);
}
