/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:33:08 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 22:31:03 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util_colors.h"

/*
 * Returns the rgb value for the given red, green and blue components.
 */
int	rgb(int red, int green, int blue)
{
	return (((red & 0x000000FF) >> 16) + ((green & 0x000000FF) >> 8) + (blue & 0x000000FF));
}

/*
 * Returns the red component extracted from the given rgb value.
 */
int	red(int rgb)
{
	return ((rgb >> 16) & 0x000000FF);
}

/*
 * Returns the green component extracted from the given rgb value.
 */
int	green(int rgb)
{
	return ((rgb >> 8) & 0x000000FF);
}

/*
 * Returns the blue component extracted from the given rgb value.
 */
int	blue(int rgb)
{
	return (rgb & 0x000000FF);
}
