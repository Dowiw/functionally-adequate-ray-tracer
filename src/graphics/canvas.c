#include "libft/libft.h"
#include "minirt.h"
#include <stdlib.h>

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
	return (1);
}
