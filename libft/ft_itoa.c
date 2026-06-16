/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 10:37:47 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/23 10:37:48 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Helper function that counters the number of digits in n
static size_t	digit_counter(long long nmbr)
{
	size_t	out;

	out = 0;
	if (nmbr < 0)
	{
		out++;
		nmbr = -nmbr;
	}
	if (nmbr == 0)
		out++;
	while (nmbr != 0)
	{
		nmbr /= 10;
		out++;
	}
	return (out);
}

//Converts an integer into a mallocated string
char	*ft_itoa(int n)
{
	char		*out;
	size_t		len;
	size_t		i;
	long long	nmbr;

	nmbr = (long long)n;
	len = digit_counter(nmbr);
	out = malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	out[len] = '\0';
	if (nmbr == 0)
		out[0] = '0';
	if (nmbr < 0)
	{
		out[0] = '-';
		nmbr = -nmbr;
	}
	i = len - 1;
	while (nmbr != 0)
	{
		out[i--] = (nmbr % 10) + '0';
		nmbr /= 10;
	}
	return (out);
}

/*
int main(void)
{
	#include <limits.h>
	char *test = ft_itoa(111);
	printf("%s\n", test);
	free(test); return (0);
}
*/
