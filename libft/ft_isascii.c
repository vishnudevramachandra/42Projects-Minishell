/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:06:45 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 14:28:26 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c < 0 || c > 127)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	c = -1;
// 	printf("isascii: %d\n", isascii(c));
// 	printf("ft_isascii: %d\n", ft_isascii(c));
// 	return (0);
// }