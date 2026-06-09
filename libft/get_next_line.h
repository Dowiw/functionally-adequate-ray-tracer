/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 16:28:58 by sstark            #+#    #+#             */
/*   Updated: 2025/06/05 14:08:25 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_filebuffer {
	int		fd;
	char	*buffer;
	ssize_t	bytes_read;
	ssize_t	i;
}	t_filebuffer;

char	*get_next_line(int fd);

char	*ft_strappend(char *str, char c);

int		ft_initbuffer(t_filebuffer *buffer, int fd);

int		ft_initstr(char **str);

char	*ft_freebuffer(t_filebuffer *buffer);

char	*ft_freebufferandresult(t_filebuffer *buffer, char *result);

#endif
