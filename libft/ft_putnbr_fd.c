/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sstark <sstark@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:52:57 by sstark            #+#    #+#             */
/*   Updated: 2025/05/12 13:52:58 by sstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_putnbrr_fd(long n, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbrr_fd(-((long) n), fd);
	}
	else
	{
		ft_putnbrr_fd((long) n, fd);
	}
}

static void	ft_putnbrr_fd(long n, int fd)
{
	if (n != 0)
	{
		ft_putnbrr_fd(n / 10, fd);
		ft_putchar_fd('0' + n % 10, fd);
	}
}

/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		printf("Important: Testing always uses fd=1 to print to the terminal!\n");
		ft_putnbr_fd(atoi(argv[1]), 1);
	}
	else
		printf("Error: Wrong arg count!\n");
	return (0);
}
*/
