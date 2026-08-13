/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmonjard <kmonjard@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 19:51:58 by kmonjard          #+#    #+#             */
/*   Updated: 2026/08/13 19:52:19 by kmonjard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Swaps pointers
 * 
 * @param a
 * @param b
 */
void	ft_swap(void *a, void *b)
{
	void	*temp;

	temp = a;
	a = b;
	b = temp;
}
