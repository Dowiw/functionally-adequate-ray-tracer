/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 11:18:36 by kmonjard          #+#    #+#             */
/*   Updated: 2025/09/25 11:18:39 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_hex(char c)
{
	if ((c >= '0' && c <= '9')
		|| (c >= 'a' && c <= 'f')
		|| (c >= 'A' && c <= 'F'))
		return (1);
	return (0);
}

/**
 * - Turn a hex string into its integer equivalent
 * - Does not check for whitespace
 */
int	ft_strtol_hex(const char *s)
{
	int	out;
	int	sign;

	out = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		s += 2;
	while (is_hex(*s) && *s)
	{
		out *= 16;
		if (*s >= '0' && *s <= '9')
			out += *s - '0';
		else if (*s >= 'a' && *s <= 'f')
			out += *s - 'a' + 10;
		else if (*s >= 'A' && *s <= 'F')
			out += *s - 'A' + 10;
		s++;
	}
	return (out * sign);
}
