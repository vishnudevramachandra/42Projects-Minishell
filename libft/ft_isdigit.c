/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:32:39 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 12:39:58 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	c = '9';
// 	printf("isdigit: %d\n", isdigit(c));
// 	printf("ft_isdigit: %d\n", ft_isdigit(c));
// 	return (0);
// }