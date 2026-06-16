/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:22:03 by sstark            #+#    #+#             */
/*   Updated: 2026/06/16 13:44:10 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../libft/libft.h"

/*
 * Parses the given string 'str' as an integer.
 *  - Integer over-/underflow are treated as a parsing failure.
 *  - Does not allow whitespace.
 *  - Allows one sign character, either '+' or '-'.
 *  - Allows leading zeros.
 * The result is stored in the 'num' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_int(int *num, char *str)
{
	long	n;
	int		i;
	int		sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	n = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		n = n * 10 + (str[i] - '0') * sign;
		if (n < INT_MIN || n > INT_MAX)
			return (0);
		i++;
	}
	*num = (int) n;
	return (1);
}

/*
 * Parses the given 'str' (see parse_int) and checks the result against the given range 'min' and 'max'.
 */
int parse_int_range(int *num, char *str, int min, int max)
{
	return (parse_int(num, str) && *num >= min && *num <= max);
}
