/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_point.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 14:12:08 by sstark            #+#    #+#             */
/*   Updated: 2026/08/05 14:17:53 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parsing.h"

int	parse_point(t_point *point, char *str)
{
	if (!parse_tuple(point, str))
		return (0);
	point->w = POINT;
	return (1);
}
