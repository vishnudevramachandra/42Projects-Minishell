/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:11:33 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/13 11:34:38 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int	sign;
	int	nbr;

	while (*str == ' ' || *str == '\f' || *str == '\n'
		|| *str == '\r' || *str == '\t' || *str == '\v')
		str++;
	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	nbr = 0;
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - 48);
		str++;
	}
	return (sign * nbr);
}

// #include <stdlib.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = " 	\f\v+123ab456";
// 	printf("atoi: %d\n", atoi(str));
// 	printf("ft_atoi: %d\n", ft_atoi(str));
// }