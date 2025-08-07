/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:51:16 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 15:07:55 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (len > 0)
	{
		((char *)b)[i] = c;
		i++;
		len--;
	}
	return (b);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[10];
// 	char	str2[10];
// 	char	c = 'a';
// 	size_t	len = 9;

// 	printf("memset: %s\n", memset(str1, c, len));
// 	printf("ft_memset: %s\n", ft_memset(str2, c, len));
// 	printf("len: %lu", len);
// 	return (0);
// }