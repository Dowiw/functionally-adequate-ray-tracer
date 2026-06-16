/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:38:41 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/13 19:38:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Copies a mem_area src to another mem_area dest based on size
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_area;
	unsigned char	*dest_area;

	i = 0;
	if (src == NULL && dest == NULL)
		return (dest);
	src_area = (unsigned char *)src;
	dest_area = (unsigned char *)dest;
	while (i < n)
	{
		dest_area[i] = src_area[i];
		i++;
	}
	return (dest);
}
