/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 12:29:34 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 12:29:36 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The manual states:
//   "If the multiplication of nmemb and size would result in
//   integer overflow, then calloc() returns an error."
// so we return NULL if nmemb * size > 2147483647.
void	*ft_calloc(size_t nmemb, size_t size)
{
	void				*result;
	unsigned long long	bytes;

	bytes = (unsigned long long) nmemb * size;
	if (bytes > 2147483647)
		return (NULL);
	result = malloc(nmemb * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, nmemb * size);
	return (result);
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 0)
		printf("No tests for %s: It's just malloc + bzero.\n", argv[0]);
	return (0);
}
*/
