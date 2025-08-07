/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:15:21 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/19 14:48:20 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	diff;

	while (n > 0)
	{
		diff = *(unsigned char *)s1 - *(unsigned char *)s2;
		if (diff)
			return (diff);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = {-128, 0, 127, 0};
// 	char	str2[] = {0, 0, 127, 0};
// 	size_t	n = 12;

// 	printf("memcmp: %d\n", memcmp(str1, str2, n));
// 	printf("ft_memcmp: %d\n", ft_memcmp(str1, str2, n));
// 	return (0);
// }