/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:48:23 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 13:09:04 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_intmin(void)
{
	char	*str;

	str = malloc(12 * sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
	return (str);
}

size_t	ft_count_digits(int n)
{
	size_t	digits;

	if (n == 0)
		return (1);
	digits = 0;
	if (n < 0)
		digits++;
	while (n)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	digits;
	size_t	nbr;

	if (n == -2147483648)
		return (ft_intmin());
	digits = ft_count_digits(n);
	str = malloc((digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[digits] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		nbr = n * -1;
	}
	else
		nbr = n;
	while (digits-- && (n >= 0 || digits > 0))
	{
		str[digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}

// #include <stdio.h>
// int	main(void)
// {
// 	int	nbr;

//    nbr = -214748364;
//    printf("%s", ft_itoa(nbr));
//    return (0);
// }