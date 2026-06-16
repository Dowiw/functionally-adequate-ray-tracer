/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 16:28:31 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/19 16:28:32 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//Trims the beginning and end of str s1 based on characters in str set
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	size_t	start_i;
	size_t	end_i;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start_i = 0;
	end_i = ft_strlen(s1);
	while (s1[start_i] && ft_strchr(set, s1[start_i]))
		start_i++;
	while (end_i > start_i && ft_strchr(set, s1[end_i - 1]))
		end_i--;
	out = malloc(sizeof(char) * (end_i - start_i + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (start_i < end_i)
		out[i++] = s1[start_i++];
	out[i] = '\0';
	return (out);
}

/*
int main(void)
{
	#include <stdio.h>

	//Regular Case
	char *test = "........Hello World.......";
	printf("%s\n", test);
	char *set = ".";
	char *out = ft_strtrim(test, set);
	printf("%s\n", out); free(out);


	return (0);
}
*/
