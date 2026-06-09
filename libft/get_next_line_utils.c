/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:28:50 by sstark            #+#    #+#             */
/*   Updated: 2025/06/19 19:23:31 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_initbuffer(t_filebuffer *buffer, int fd)
{
	if (buffer->fd != fd || buffer->buffer == NULL)
	{
		buffer->fd = fd;
		if (BUFFER_SIZE < 1)
			return (0);
		buffer->buffer = malloc(BUFFER_SIZE);
		if (buffer->buffer == NULL)
			return (0);
		buffer->bytes_read = read(buffer->fd, buffer->buffer, BUFFER_SIZE);
		buffer->i = 0;
	}
	return (1);
}

char	*ft_freebufferandresult(t_filebuffer *buffer, char *result)
{
	ft_freebuffer(buffer);
	free(result);
	return (NULL);
}

char	*ft_freebuffer(t_filebuffer *buffer)
{
	free(buffer->buffer);
	buffer->fd = -1;
	buffer->buffer = NULL;
	buffer->bytes_read = 0;
	buffer->i = 0;
	return (NULL);
}

int	ft_initstr(char **str)
{
	*str = malloc(1);
	if (*str != NULL)
	{
		(*str)[0] = '\0';
		return (1);
	}
	return (0);
}

char	*ft_strappend(char *str, char c)
{
	char	*result;
	size_t	len;
	size_t	i;

	len = 0;
	while (str[len] != '\0')
		len++;
	result = malloc(len + 1 + 1);
	if (result == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = c;
	result[i + 1] = '\0';
	free(str);
	return (result);
}
