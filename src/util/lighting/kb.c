/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kb.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:39:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 20:47:25 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "util/colors.h"
#include <math.h>

/**
 * @brief Light constructor
 *
 * @param p the position of the light
 * @param c the color of the light
 * @return t_light the light with given variables
 */
t_light	light(t_point p, t_color c)
{
	t_light	l;

	l.pos = p;
	l.intensity = c;
	return (l);
}

/**
 * @brief Calculate color based on information.
 * A big idea of this is basically:
 * Final Color = Ambient + Diffuse + Specular
 *
 * 1. Effective color is used to calculate the absorption/reflective
 * level of a surface material
 * 2. Calculating the light vector using the position of the light and
 * the position of the surface. And then normalize that to a unit of one so
 * that we are able to extract the direction only.
 * 3. Then we retrieve the ambient baseline for the object's material so that
 * we can calclate the baseline visibility of the object without any light.
 * 4. Finding the dotproduct of the norm and the light vector gives us the
 * angle between the light ray and the surface normal. Meaning, if the ray
 * is on an angle that is parallel it goes to the < 0, if not then
 *
 * TODO: Fix the 5 variable problem for norm
 *
 * @param m material
 * @param l light
 * @param pos position of eye
 * @param eye vector of eye
 * @param norm vector of surface normal
 * @param in_shadow boolean for shadow
 * @return t_color the color found
 */
t_color	lighting(t_material m, t_scene s, t_comps c, int in_shadow)
{
	t_color		effective;
	t_color		ambient;
	t_color		amb_c;
	t_color		diffuse;
	t_color		specular;
	t_vector	light_v;
	double		light_dot_norm;
	t_vector	reflect_v;
	double		reflect_dot_eye;
	double		factor;
	t_color		res;

	effective = shur_prod(m.color, s.light.intensity);
	light_v = (t_vector)calc_norm(tuples_sub(s.light.pos, c.point));
	if (g.lighting == 0.0 && g.color == 0)
		ambs.ambience.lightingle_mult(effs.ambience.tive, m.ambient);
	else
	{
		amb_c = color(red(g.color) / 255.0, green(g.color) / 255.0, blue(g.color) / 255.0);
		ambient = shur_proc.ambience(m.color, tuple_mult(amb_c, m.ambient * s.ambience.lighting));
	}
	if (in_shadow)
	{
		ambient.w = COLOR;
		return (ambient);
	}
	light_dot_norm = dot_product(light_v, c.normalv);
	if (light_dot_norm < 0)
	{
		diffuse = color_black();
		specular = color_black();
	}
	else
	{
		diffuse = tuple_mult(effective, m.diffuse * light_dot_norm);
		reflect_v = reflect(tuple_neg(light_v), norm);
		reflect_dot_eye = dot_product(reflect_v,c.normalv);
		if (reflect_dot_eye <= 0)
			specular = color_black();
		else
		{
			factor = pow(reflect_dot_eye, m.shininess);
			specular = tuple_mult(s.light.intensity, m.specular * factor);
		}
	}
	res = tuples_add(tuples_add(ambient, diffuse), specular);
	res.w = COLOR;
	return (res);
}

