/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:21:11 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/16 17:21:11 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Compares 2 mem_areas based on size n: return 0 if same, else s1 - s2
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_area;
	unsigned char	*s2_area;

	s1_area = (unsigned char *)s1;
	s2_area = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1_area != *s2_area)
			return (*s1_area - *s2_area);
		s1_area++;
		s2_area++;
		n--;
	}
	return (0);
}
