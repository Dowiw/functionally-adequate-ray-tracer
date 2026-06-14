/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:41:44 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/18 14:42:21 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Look for string little in string big: return NULL if N/A, else &big
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!big && !len)
		return (NULL);
	if (little[0] == '\0')
		return ((char *)big);
	if (len > ft_strlen(big))
		len = ft_strlen(big);
	while (i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && (i + j) < len)
		{
			j++;
			if (little[j] == '\0')
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}

/*
int main(void)
{
	#include <stdio.h>
	#include <bsd/string.h>
	char *test = ft_strnstr("", "aaaaa", -1);
	char *test1 = strnstr("", "aaaaa", -1);
	printf("%s\n", test);
	printf("%s\n", test1);

	char *test2 = ft_strnstr("", "", 0);
	char *test3 = strnstr("", "", 0);
	printf("%s\n", test2);
	printf("%s\n", test3);
}
*/
