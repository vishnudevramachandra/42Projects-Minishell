/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 12:20:34 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 12:31:58 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
		return (0);
	return (1);
}

// #include <ctype.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	c = 'n';
// 	printf("isalpha: %d\n", isalpha(c));
// 	printf("ft_isalpha: %d\n", ft_isalpha(c));
// 	return (0);
// }