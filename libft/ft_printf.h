/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 14:29:18 by sstark            #+#    #+#             */
/*   Updated: 2025/06/19 16:31:43 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

int	ft_printf(const char *str, ...);

int	ft_printchar(char c);

int	ft_printnbr(int n);

int	ft_printptr(void *ptr);

int	ft_printstr(char *str);

int	ft_printunbr(unsigned int n);

int	ft_printunbr_base(unsigned int n, char *base);

#endif
