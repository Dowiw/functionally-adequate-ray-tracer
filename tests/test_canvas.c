#include "libunit_assert.h"
#include "minirt.h"
#include <stdlib.h>

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