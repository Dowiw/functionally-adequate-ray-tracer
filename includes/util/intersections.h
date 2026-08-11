/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:41:54 by sstark            #+#    #+#             */
/*   Updated: 2026/08/10 17:05:39 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "scene.h"

t_intersections	intersections_create(void);

t_intersections	intersections_add(t_intersections xs, t_intersection *intersection);

t_intersections	intersections_add_all(t_intersections xs, t_intersections to_add);

int				intersections_len(t_intersections xs);

void			free_intersections(t_intersections xs);

int				intersections_compare(t_intersection *a, t_intersection *b);

void			intersections_sort(t_intersections *xs);

#endif
