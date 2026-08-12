/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:22:03 by sstark            #+#    #+#             */
/*   Updated: 2026/08/09 15:43:17 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "libft/libft.h"
#include "parsing.h"

/*
 * Parses the given string 'str' as an integer.
 *  - Integer over-/underflow are treated as a parsing failure.
 *  - Does not allow whitespace.
 *  - Allows one sign character, either '+' or '-'.
 *  - Allows leading zeros.
 * The result is stored in the 'num' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_int(t_scene *scene, int *num, char *str)
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
		return (parse_error(scene, "Not a valid integer"));
	n = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (parse_error(scene, "Not a valid integer"));
		n = n * 10 + (str[i] - '0') * sign;
		if (n < INT_MIN || n > INT_MAX)
			return (parse_error(scene, "Number exceeds the integer limit"));
		i++;
	}
	*num = (int) n;
	return (1);
}

/*
 * Parses the given 'str' (see parse_int) and checks the result against the
 * given range 'min' and 'max'.
 */
int	parse_int_range(t_scene *scene, int *num, char *str, int min, int max)
{
	if (!parse_int(scene, num, str))
		return (0);
	if (*num < min)
		return (parse_error(scene, "Number is too small"));
	if (*num > max)
		return (parse_error(scene, "Number is too big"));
	return (1);
}
