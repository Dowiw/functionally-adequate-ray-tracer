#include "libft/get_next_line.h"
#include "libunit_assert.h"
#include "minirt.h"
#include <fcntl.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	test_canvas(void)
{
	t_canvas	c;
	t_tuple		black = {0, 0, 0, COLOR};
	int		w = 10;
	int		h = 20;

	if (!canvas_create(&c, w, h))
		return (1);
	UNIT_ASSERT_EQ(c.width, w);
	UNIT_ASSERT_EQ(c.height, h);
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
		{
			UNIT_ASSERT(compare_tuples(&black, &c.pixels[i * w + j]));
		}
	}
	free(c.pixels);

	return (0);
}

int	test_canvas_place(void)
{
	t_canvas	c;
	t_tuple		red = {1, 0, 0, COLOR};
	int			w = 10;
	int			h = 20;

	if (!canvas_create(&c, w, h))
		return (1);
	write_pixel(&c, 2, 3, red);
	t_tuple		color = view_pixel(&c, w, h);
	UNIT_ASSERT(compare_tuples(&red, &color));
	free(c.pixels);

	return (0);
}

int	test_canvas_ppm(void)
{
	t_canvas	c;
	t_tuple		c1 = {1.5, 0, 0, COLOR};
	t_tuple		c2 = {0, 0.5, 0, COLOR};
	t_tuple		c3 = {-0.5, 0, 1, COLOR};
	
	if (!canvas_create(&c, 5, 3))
		return 1;
	write_pixel(&c, 0, 0, c1);
	write_pixel(&c, 2, 1, c2);
	write_pixel(&c, 4, 2, c3);

	char	*filename = canvas_to_ppm(&c);
	if (!filename)
		return 1;
	char	*a;
	int fd = open(filename, O_RDONLY);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "P3\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "5 3\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "255\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT(ft_strcmp(a, "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n") == 0);
	free(a);
	a = get_next_line(fd);
	UNIT_ASSERT_EQ(a, NULL);

	unlink(filename);
	free(filename);
	return 0;
}