/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 22:06:51 by sstark            #+#    #+#             */
/*   Updated: 2026/08/19 18:52:13 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_H
# define ARRAYS_H

void	**array_create(void);

void	**array_add(void **array, void *elem);

void	**array_add_all(void **array, void **elems);

int		array_len(void **array);

void	free_array(void **array);

#endif
