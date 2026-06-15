/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:22:03 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 21:26:04 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"

/*
 * Parses the given string 'str' as an integer.
 *  - Does not handle integer over- or underflow.
 *  - Does not allow whitespace.
 *  - Allows one sign character, either '+' or '-'.
 *  - Allows leading zeros.
 * The result is stored in the 'num' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_int(int *num, char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!ft_isdigit(str[i]))
		return (0);
	*num = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (0);
		*num = *num * 10 + (str[i] - '0') * sign;
		i++;
	}
	return (1);
}
