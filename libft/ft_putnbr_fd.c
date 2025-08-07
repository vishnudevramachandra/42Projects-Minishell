/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 14:34:35 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 13:49:09 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

static size_t	nbr_of_digits(int n)
{
	if (!(n / 10))
		return (1);
	return (1 + nbr_of_digits(n / 10));
}

static int	power(int nbr, size_t exp)
{
	if (exp == 0)
		return (1);
	return (nbr * power(nbr, exp - 1));
}

static void	putnbr_subfcn(int n, int pow_of_ten, int fd)
{
	char	c;

	while (pow_of_ten > 0)
	{
		if (n < 0)
			c = '0' - (n / pow_of_ten);
		else
			c = '0' + (n / pow_of_ten);
		write(fd, &c, 1);
		n %= pow_of_ten;
		pow_of_ten /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		write(fd, "-", 1);
	putnbr_subfcn(n, power(10, nbr_of_digits(n) - 1), fd);
}

// #include <stdio.h>

// int	main(void)
// {
// 	int i = (-2147483647 -1);
// 	ft_putnbr_fd(i, 1);
// 	printf("\n");
// 	printf("%d\n", i);
// 	return (0);
// }