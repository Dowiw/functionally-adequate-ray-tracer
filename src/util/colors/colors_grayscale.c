/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_grayscale.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:23:08 by kmonjard          #+#    #+#             */
/*   Updated: 2026/07/02 13:23:30 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minirt.h"

/**
 * @brief Color black constructor
 *
 * @return t_color black color
 */
t_color	color_black(void)
{
	t_color	b;

	b.x = 0;
	b.y = 0;
	b.z = 0;
	b.w = COLOR;
	return (b);
}
