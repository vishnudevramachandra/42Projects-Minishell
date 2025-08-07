/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:19:11 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 14:31:28 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c < 040 || c > 0176)
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	c = 127;
// 	printf("isprint: %d\n", isprint(c));
// 	printf("ft_isprint: %d\n", ft_isprint(c));
// 	return (0);
// }