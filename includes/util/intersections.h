/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 10:41:54 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 11:18:21 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECTIONS_H
# define INTERSECTIONS_H

# include "scene.h"

t_intersection	**intersections_create(void);

t_intersection	**intersections_add(t_intersection **array, t_intersection *intersections);

t_intersection	**intersections_add_all(t_intersection **array, t_intersection **intersections);

int				intersections_len(t_intersection **array);

void			free_intersections(t_intersection **array);

int				intersections_compare(t_intersection *a, t_intersection *b);

void			intersections_sort(t_intersection **array);

#endif
