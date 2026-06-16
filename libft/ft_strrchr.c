/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:58:16 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/16 10:58:17 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Find char c in string s: return last found address, NULL otherwise
char	*ft_strrchr(const char *s, int c)
{
	char	*out;

	out = NULL;
	while (*s)
	{
		if (*s == (char)c)
			out = (char *)s;
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (out);
}
