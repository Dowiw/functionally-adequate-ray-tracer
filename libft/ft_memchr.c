/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:48:10 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/16 15:48:12 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Find c in mem_area s based on size n
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_area;

	i = 0;
	s_area = (unsigned char *)s;
	while (i < n)
	{
		if (s_area[i] == (unsigned char)c)
			return (s_area + i);
		i++;
	}
	return (NULL);
}
