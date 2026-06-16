/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:02:24 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/20 20:44:55 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 1

/*
	Files get_next_line.c and get_next_line_utils.c uses both headers.
	<stdlib.h> is used for malloc and free.
	<unistd.h> is used for read.
*/
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

/*
	A function that returns a new line from a file descriptor.
	New line is defined as a string of chars with '\n' in it.
	Uses <stdlib.h> for malloc and free.
	- Pass -1 to free the static line_buffer
*/
char	*get_next_line(int fd);

// UTILITIES
/*
	Utility to allocate nmemb number of elements with sizeof(size).
	Will set the allocated elements to 0.
	Returns (NULL) if invalid parameters & allocation fail.
*/
void	*ft_calloc(size_t nmemb, size_t size);

/*
	Utility to return a new allocated string that concats s1 and s2.
	s1 is the prefix, s2 is the suffix.
	Return (NULL) for invalid input and malloc fail.
*/
char	*ft_strjoin(const char *s1, const char *s2);

/*
	Utility to return bool value if char c is found in string s.
	Returns (1) if found. Returns (0) if not found.
	If c is '\0', returns (1).
*/
int		ft_strchr_bool(const char *s, char c);

/*
	Helper function that reads file into the static buffer.
	Uses strjoin to combine read buffer into line buffer.
	Returns NULL for allocation fails & read fails.
*/
char	*ft_read_file(int fd, char *line_buffer);

/*
	Utility to free line_buffer.
	Checks if there is line_buffer and frees.
*/
void	ft_free_buffer(char **line_buffer);

#endif
