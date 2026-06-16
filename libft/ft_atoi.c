/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 16:00:29 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/18 16:00:30 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Converts string to int: checks isspace(3), one + | - sign, then digit
int	ft_atoi(const char *nptr)
{
	int	out;
	int	sign;

	out = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		out = out * 10 + (*nptr - '0');
		nptr++;
	}
	return (out * sign);
}
