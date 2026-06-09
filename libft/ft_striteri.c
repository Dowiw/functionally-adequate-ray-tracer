/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:18 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:52:19 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}

/*
#include <stdio.h>
static void	printing(unsigned int i, char *c);
int	main(int argc, char **argv)
{
	if (argc == 2)
		ft_striteri(argv[1], &printing);
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}

static void	printing(unsigned int i, char *c)
{
	printf("%d: %c\n", i, *c);
}
*/
