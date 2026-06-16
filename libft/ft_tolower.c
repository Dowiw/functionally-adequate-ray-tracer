/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 10:41:14 by kmonjard          #+#    #+#             */
/*   Updated: 2025/05/16 10:41:17 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//Convert char c to lowercase: return c if not upper case letter
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}
