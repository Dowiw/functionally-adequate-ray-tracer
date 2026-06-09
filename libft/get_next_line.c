/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:28:40 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 20:00:32 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_filebuffer	buffer;
	char				*result;

	if (!ft_initbuffer(&buffer, fd))
		return (NULL);
	if (!ft_initstr(&result))
		return (ft_freebuffer(&buffer));
	while (buffer.bytes_read > 0)
	{
		while (buffer.i < buffer.bytes_read)
		{
			result = ft_strappend(result, buffer.buffer[buffer.i]);
			if (result == NULL)
				return (ft_freebuffer(&buffer));
			if (buffer.buffer[buffer.i++] == '\n')
				return (result);
		}
		buffer.bytes_read = read(buffer.fd, buffer.buffer, BUFFER_SIZE);
		buffer.i = 0;
	}
	if (buffer.bytes_read == -1 || result[0] == '\0')
		return (ft_freebufferandresult(&buffer, result));
	return (result);
}

/*
#include <fcntl.h>
#include <stdio.h>
int		main(int argc, char **argv)
{
	int		fd;
	char	*line;

	if (argc != 2)
	{
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		return (0);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
