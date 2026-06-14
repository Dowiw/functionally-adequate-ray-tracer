/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 14:59:26 by kmonjard          #+#    #+#             */
/*   Updated: 2025/07/15 14:55:14 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h> // all functions need this for write

/*
	my printf function that implements the formats:
	`%%, %c, %s, %i, %x, %X, %u, %d`
*/
int	ft_printf(const char *s, ...);

// write out character to stdout, returns 1
int	ft_putchar(int c);

// write out a string of characters to stdout
int	ft_putstr(const char *str);

// write out an integer to stdout
int	ft_putint(int n);

// write out the base-16 format of a ptr to stdout
int	ft_putptr(void *p);

// write out an unsigned int in stdout
int	ft_putint_u(unsigned int n);

// write out the low-case hex format of an unsigned int in stdout
int	ft_puthex_lowcase(unsigned int n);

// write out the big-case hex format of an unsigned int in stdout
int	ft_puthex_upcase(unsigned int n);

#endif
