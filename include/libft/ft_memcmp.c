/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:41:28 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 16:30:34 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (n > i)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char s1[] = "atoms\0\0\0\0";
// 	char s2[] = "atoms\0abc";
// 	printf("%d\n", ft_memcmp(s1, s2, 8));
// 	printf("%d\n", memcmp(s1, s2, 8));
// 	return(0);
// }