/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 11:45:53 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 17:43:07 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Material constructor.
 *
 * Default material.
 * - Default color: White
 * - Ambience factor: 0.1
 * - Diffuse factor: 0.9
 * - Specular factor: 0.9
 * - Shininess factor: 200.0
 *
 * @return t_material material struct
 */
t_material	material(void)
{
	t_material	m;

	m.color = color(1, 1, 1);
	m.ambient = 0.1;
	m.diffuse = 0.9;
	m.specular = 0.9;
	m.shininess = 200.0;
	return (m);
}
