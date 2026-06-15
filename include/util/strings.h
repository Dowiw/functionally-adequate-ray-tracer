/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 20:20:05 by sstark            #+#    #+#             */
/*   Updated: 2026/06/15 23:27:51 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGS_H
# define STRINGS_H

int		string_equals(char *str1, char *str2);

int		string_endswith(char *str, char *suffix);

char	*string_remove_suffix(char *str, char *suffix);

#endif
