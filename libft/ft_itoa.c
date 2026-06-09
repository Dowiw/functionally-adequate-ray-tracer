/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:51:59 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:51:59 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_itoa_len(int n);

static void		ft_itoa_populate(char *result, long n, size_t len);

char	*ft_itoa(int n)
{
	char	*result;
	size_t	len;

	if (n == 0)
	{
		return (ft_strdup("0"));
	}
	len = ft_itoa_len(n);
	result = ft_calloc(len + 1, sizeof(char));
	if (result == NULL)
	{
		return (NULL);
	}
	ft_itoa_populate(result, (long) n, len);
	return (result);
}

static size_t	ft_itoa_len(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
		len = 1;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

static void	ft_itoa_populate(char *result, long n, size_t len)
{
	size_t	i;

	if (n < 0)
	{
		result[0] = '-';
		n = -n;
	}
	i = 0;
	while (n != 0)
	{
		result[len - 1 - i] = '0' + n % 10;
		n = n / 10;
		i++;
	}
	result[len] = '\0';
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("%s\n", ft_itoa(atoi(argv[1])));
		printf("%d\n", atoi(argv[1]));
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
