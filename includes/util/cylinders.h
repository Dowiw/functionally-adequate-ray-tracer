/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinders.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:01:40 by sstark            #+#    #+#             */
/*   Updated: 2026/08/04 10:41:40 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDERS_H
# define CYLINDERS_H

# include "scene.h"

t_cylinder	**cylinders_create(void);

t_cylinder	cylinder_create(void);

t_cylinder	**cylinders_add(t_cylinder **array, t_cylinder *cylinder);

int			cylinders_len(t_cylinder **array);

void		free_cylinders(t_cylinder **array);

#endif
