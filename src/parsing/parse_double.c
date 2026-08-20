/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 21:37:50 by sstark            #+#    #+#             */
/*   Updated: 2026/08/20 22:26:09 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parsing.h"

static int	parse_double_before_decimal(double *num, char *str, int *i,
				int sign);
static int	parse_double_after_decimal(double *num, char *str, int *i,
				int sign);

/*
 * Parses the given string 'str' as a double.
 *  - Does not handle over- or underflow.
 *  - Does not allow whitespace.
 *  - Allows one sign character, either '+' or '-'.
 *  - Allows leading zeros.
 * The result is stored in the 'num' pointer.
 * Returns true if the parsing was successful.
 */
int	parse_double(t_scene *scene, double *num, char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!parse_double_before_decimal(num, str, &i, sign))
		return (parse_error(scene, "Not a valid number"));
	if (str[i] == '.')
	{
		i++;
		if (!parse_double_after_decimal(num, str, &i, sign))
			return (parse_error(scene, "Not a valid number"));
	}
	return (1);
}

/*
 * Parses the given 'str' (see parse_double) and checks the result against the
 * given range 'min' and 'max'.
 */
int	parse_double_range(t_scene *scene, double *num, char *str,
		double bounds[2])
{
	if (!parse_double(scene, num, str))
		return (0);
	if (*num < bounds[0])
		return (parse_error(scene, "Number is too small"));
	if (*num > bounds[1])
		return (parse_error(scene, "Number is too big"));
	return (1);
}

static int	parse_double_before_decimal(double *num, char *str, int *i,
				int sign)
{
	*num = 0.0;
	if (!ft_isdigit(str[*i]))
		return (0);
	while (str[*i] != '.' && str[*i] != '\0')
	{
		if (!ft_isdigit(str[*i]))
			return (0);
		*num = *num * 10.0 + (str[*i] - '0') * sign;
		*i += 1;
	}
	return (1);
}

static int	parse_double_after_decimal(double *num, char *str, int *i,
				int sign)
{
	long	divisor;

	if (!ft_isdigit(str[*i]))
		return (0);
	divisor = 10;
	while (str[*i] != '\0')
	{
		if (!ft_isdigit(str[*i]))
			return (0);
		*num = *num + (double)((str[*i] - '0') * sign) / divisor;
		divisor *= 10;
		*i += 1;
	}
	return (1);
}
