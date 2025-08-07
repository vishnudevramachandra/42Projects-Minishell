/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:15:01 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 10:18:23 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (len > 0)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
		len--;
	}
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[11] = "home alone";
// 	char	str2[11] = "heim";

// 	printf("memmove: %s\n", memcpy(str1, str2, 4));
// 	printf("ft_memmove: %s\n", ft_memcpy(str2, str1, 11));
// 	return (0);
// }