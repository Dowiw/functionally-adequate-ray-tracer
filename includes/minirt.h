/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 19:30:47 by sstark            #+#    #+#             */
/*   Updated: 2026/06/09 19:30:59 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# ifndef UNIT_EPSILON
#  define UNIT_EPSILON 0.00001
# endif

# define VECTOR 0.0
# define POINT 1.0
# define INVALID_NEG -1.0
# define INVALID_POS 2.0

typedef struct s_tuple
{
	double			x;
	double			y;
	double			z;
	double			w;
}	t_tuple;

/** ######################################################################### *
 *  TUPLES                                                                  # *
 *  ######################################################################### */

// tuple_utils.c

int	compare_doubles(const double a, const double b);
int	compare_tuples(const t_tuple *a, const t_tuple *b);
t_tuple	add_tuples(const t_tuple a, const t_tuple b);
t_tuple sub_tuples(const t_tuple a, const t_tuple b);

#endif
