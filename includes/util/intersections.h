/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:41:54 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:52:00 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "scene.h"

t_intersects	intersections_create(void);

t_intersects	intersections_add(t_intersects xs, t_intersect *intersection);

t_intersects	intersections_add_all(t_intersects xs, t_intersects to_add);

int				intersections_len(t_intersects xs);

void			free_intersections(t_intersects xs);

void			intersections_sort(t_intersects *xs);

#endif
