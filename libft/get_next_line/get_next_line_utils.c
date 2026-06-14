/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 13:11:47 by kmonjard          #+#    #+#             */
/*   Updated: 2025/06/20 20:45:08 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_file(int fd, char *line_buffer)
{
	char	*tmp;
	char	*buffer;
	ssize_t	read_bytes;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while (ft_strchr_bool(line_buffer, '\n') == 0 && read_bytes > 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		tmp = ft_strjoin(line_buffer, buffer);
		free(line_buffer);
		line_buffer = tmp;
	}
	if (read_bytes == -1)
	{
		free(buffer);
		return (NULL);
	}
	free(buffer);
	return (line_buffer);
}

void	ft_free_buffer(char **line_buffer)
{
	if (line_buffer && *line_buffer)
	{
		free(*line_buffer);
		*line_buffer = NULL;
	}
}

int	ft_strchr_bool(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (1);
		s++;
	}
	if (c == '\0')
		return (1);
	return (0);
}
