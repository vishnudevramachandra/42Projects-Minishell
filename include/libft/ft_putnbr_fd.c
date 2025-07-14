/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:46:00 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 13:14:14 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
	}
	n = n % 10;
	ft_putchar_fd(n + 48, fd);
}

// int main(void)
// {
// 	int fd;

// 	fd = 1;
// 	ft_putnbr_fd(12345, fd);
// 	write(fd, "\n", 1);
// 	ft_putnbr_fd(-12345, fd);
// 	write(fd, "\n", 1);
// 	ft_putnbr_fd(0, fd);
// 	write(fd, "\n", 1);
// 	ft_putnbr_fd(-2147483648, fd);
// 	write(fd, "\n", 1);
// 	return (0);
// }