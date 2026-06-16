/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:04:51 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/18 18:04:52 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Duplicates string s to another string in memory
char	*ft_strdup(const char *s)
{
	char	*out;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = 0;
	while (s[s_len])
		s_len++;
	out = malloc(sizeof(char) * (s_len + 1));
	if (!out)
		return (NULL);
	while (i < s_len)
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
