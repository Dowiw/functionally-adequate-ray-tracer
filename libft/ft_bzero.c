/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 19:09:49 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/13 19:09:50 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Set memory area to '\0' based on size n
void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem_area;

	i = 0;
	mem_area = (unsigned char *)s;
	while (i < n)
	{
		mem_area[i] = '\0';
		i++;
	}
}
