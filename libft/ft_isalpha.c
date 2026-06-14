/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:47:59 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/12 11:48:02 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Checks for an alphabetic character: returns 0 for non-alphabets
int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
