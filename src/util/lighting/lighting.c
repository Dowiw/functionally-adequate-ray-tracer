/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/02 13:39:41 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/19 19:12:29 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "minirt.h"
#include "scene.h"
#include "types.h"
#include "util/colors.h"

/**
 * @brief Light constructor
 *
 * @param p position of light source
 * @param c color intensity of light source
 * @return t_light constructed light struct
 */
t_light	light(t_point p, t_color c)
{
	t_light	l;

	l.pos = p;
	l.intensity = c;
	return (l);
}

/**
 * @brief Computes ambient light component for a material surface.
 *
 * @param m material properties
 * @param s scene containing ambient light configuration
 * @return t_color ambient lighting result
 */
static t_color	calc_ambient(t_material m, t_scene s)
{
	t_color	effective;
	t_color	amb_color;
	double	factor;

	effective = shur_prod(m.color, s.light.intensity);
	if (s.ambience.lighting == 0.0 && s.ambience.color == 0)
		return (tuple_mult(effective, m.ambient));
	factor = m.ambient * s.ambience.lighting;
	amb_color = color(red(s.ambience.color) / 255.0,
			green(s.ambience.color) / 255.0,
			blue(s.ambience.color) / 255.0);
	return (shur_prod(m.color, tuple_mult(amb_color, factor)));
}

/**
 * @brief Computes diffuse reflection based on Lambert's cosine law.
 *
 * @param m material properties
 * @param light light source info
 * @param light_dot_norm dot product between light vector and surface normal
 * @return t_color diffuse light contribution
 */
static t_color	calc_diffuse(t_material m, t_light light, double light_dot_norm)
{
	t_color	effective;

	if (light_dot_norm <= 0.0)
		return (color_black());
	effective = shur_prod(m.color, light.intensity);
	return (tuple_mult(effective, m.diffuse * light_dot_norm));
}

/**
 * @brief Computes specular highlight based on Phong reflection model.
 *
 * @param m material properties
 * @param light light source info
 * @param light_v normalized direction vector towards light
 * @param c precomputed ray intersection details
 * @return t_color specular highlight contribution
 */
static t_color	calc_specular(t_material m, t_light light, t_vector light_v,
					t_comps c)
{
	t_vector	reflect_v;
	double		reflect_dot_eye;
	double		factor;

	reflect_v = reflect(tuple_neg(light_v), c.normalv);
	reflect_dot_eye = dot_product(reflect_v, c.eyev);
	if (reflect_dot_eye <= 0.0)
		return (color_black());
	factor = pow(reflect_dot_eye, m.shininess);
	return (tuple_mult(light.intensity, m.specular * factor));
}

/**
 * @brief Computes total Phong illumination at a point:
 *        Final Color = Ambient + Diffuse + Specular
 *
 * @param m material properties
 * @param s scene information
 * @param c precomputed intersection data (point, eyev, normalv)
 * @param in_shadow flag indicating whether surface point is in shadow
 * @return t_color total illuminated color
 */
t_color	lighting(t_material m, t_scene s, t_comps c, int in_shadow)
{
	t_vector	light_v;
	double		light_dot_norm;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;

	ambient = calc_ambient(m, s);
	if (in_shadow)
	{
		ambient.w = COLOR;
		return (ambient);
	}
	light_v = (t_vector)calc_norm(tuples_sub(s.light.pos, c.point));
	light_dot_norm = dot_product(light_v, c.normalv);
	diffuse = calc_diffuse(m, s.light, light_dot_norm);
	if (light_dot_norm < 0.0)
		specular = color_black();
	else
		specular = calc_specular(m, s.light, light_v, c);
	ambient = tuples_add(tuples_add(ambient, diffuse), specular);
	ambient.w = COLOR;
	return (ambient);
}
