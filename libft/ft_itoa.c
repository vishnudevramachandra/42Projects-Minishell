/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 13:48:10 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 18:05:33 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

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

static void	fill_digits(char *s, int pow_of_ten, int n)
{
	while (pow_of_ten > 0)
	{
		if (n < 0)
			*s = '0' - (n / pow_of_ten);
		else
			*s = '0' + (n / pow_of_ten);
		s++;
		n %= pow_of_ten;
		pow_of_ten /= 10;
	}
}

char	*ft_itoa(int n)
{
	char			*str;
	size_t			n_digits;
	size_t			i;

	n_digits = nbr_of_digits(n);
	if (n < 0)
		str = (char *)malloc((n_digits + 2) * sizeof(char));
	else
		str = (char *)malloc((n_digits + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	if (n < 0)
	{
		str[i] = '-';
		i++;
	}
	fill_digits(&str[i], power(10, n_digits - 1), n);
	str[i + n_digits] = '\0';
	return (str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str;

// 	str = ft_itoa(-132);
// 	printf("ft_itoa: %s\n", str);
// 	free(str);
// 	return (0);
// }