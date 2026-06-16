/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:09:42 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/18 17:09:44 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

//Allocate nmemb elements of size bytes to 0, should check overflow
void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*out;
	size_t			i;
	size_t			total;
	unsigned char	*setter;

	i = 0;
	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	total = nmemb * size;
	out = malloc(total);
	if (!out)
		return (NULL);
	setter = out;
	while (i < total)
		setter[i++] = 0;
	return (out);
}
