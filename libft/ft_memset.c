/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:13:27 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/13 19:13:28 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Set memory area to 'c' based on size n
void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*mem_area;

	i = 0;
	mem_area = (unsigned char *)s;
	while (i < n)
	{
		mem_area[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
