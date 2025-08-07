/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:08:28 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 10:18:28 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	if (dst > src)
	{
		while (len > 0)
		{
			((char *)dst)[len - 1] = ((char *)src)[len - 1];
			len--;
		}
	}
	else
	{
		i = 0;
		while (len > 0)
		{
			((char *)dst)[i] = ((char *)src)[i];
			i++;
			len--;
		}
	}
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[11] = "home alone";

// 	printf("memmove: %s\n", memmove(&str1[0], &str1[0], 11));
// 	ft_memmove(&str1[6], &str1[0], 4);
// 	printf("ft_memmove: %s\n", str1);
// 	return (0);
// }