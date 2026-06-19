/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/16 11:48:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/06/19 11:48:42 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minirt.h"
#include <linux/limits.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>

/**
 * @brief Initializes the canvas struct passed by reference
 * 
 * @param canvas the canvas pointer
 * @param width width
 * @param height height
 * @return returns 1 for sucess, 0 for malloc error
 */
int	canvas_create(t_canvas *canvas, int width, int height)
{
	canvas->width = width;
	canvas->height = height;
	canvas->pixels = malloc(sizeof(t_tuple) * (width * height));
	if (!canvas->pixels)
		return (0);
	ft_bzero(canvas->pixels, width * height * sizeof(t_tuple));
	for (int i = 0; i < width * height; i++)
		canvas->pixels[i].w = COLOR;
	return (1);
}

/**
 * @brief Write a tuple color pixel inside the canvas.
 * 
 * @param canvas canvas pointer
 * @param x x-coordinate
 * @param y y-coordinate
 * @param color tuple color
 */
void	write_pixel(t_canvas *canvas, int x, int y, t_tuple color)
{
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
		canvas->pixels[y * canvas->width + x] = color;
}

/**
 * @brief View the pixel at the coordinates and return the pixel.
 * 
 * @param canvas canvas pointer
 * @param x x-coordinate
 * @param y y-coordinate
 * @return t_tuple color at pixel
 */
t_tuple	view_pixel(t_canvas *canvas, int x, int y)
{
	t_tuple	empty;

	empty.x = 0;
	empty.y = 0;
	empty.z = 0;
	empty.w = INVALID_NEG;
	if (x >= 0 && x < canvas->width && y >= 0 && y < canvas->height)
		return (canvas->pixels[y * canvas->width + x]);
	return (empty);
}

/**
 * @brief Saves canvas to a PPM file with a timestamp.
 * 
 * @param canvas canvas pointer
 */
char	*canvas_to_ppm(t_canvas *canvas)
{
	struct timeval	tv;
	char			filename[PATH_MAX];
	char			*sec_str;
	int				fd;
	int				x;
	int				y;
	t_tuple			pixel;

	gettimeofday(&tv, NULL);
	sec_str = ft_itoa(tv.tv_sec);
	ft_strlcpy(filename, "canvas_", sizeof(filename));
	ft_strlcat(filename, sec_str, sizeof(filename));
	ft_strlcat(filename, ".ppm", sizeof(filename));
	free(sec_str);
	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (NULL);
	ft_putstr_fd("P3\n", fd);
	ft_putnbr_fd(canvas->width, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(canvas->height, fd);
	ft_putstr_fd("\n255\n", fd);
	y = 0;
	while (y < canvas->height)
	{
		x = 0;
		while (x < canvas->width)
		{
			pixel = view_pixel(canvas, x, y);
			ft_putnbr_fd(clamp_color(pixel.x), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(clamp_color(pixel.y), fd);
			ft_putchar_fd(' ', fd);
			ft_putnbr_fd(clamp_color(pixel.z), fd);
			if (x < canvas->width - 1)
				ft_putchar_fd(' ', fd);
			x++;
		}
		ft_putchar_fd('\n', fd);
		y++;
	}
	close(fd);
	return (ft_strdup(filename));
}