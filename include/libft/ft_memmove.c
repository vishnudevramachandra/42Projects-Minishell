/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:49:17 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 17:12:27 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*newdst;
	unsigned char	*newsrc;
	size_t			i;

	i = 0;
	newdst = (unsigned char *)dst;
	newsrc = (unsigned char *)src;
	if (dst == src || len == 0)
		return (dst);
	if (newdst > newsrc && newdst < newsrc + len)
	{
		while (len-- > 0)
			newdst[len] = newsrc[len];
	}
	else
	{
		while (i < len)
		{
			newdst[i] = newsrc[i];
			i++;
		}
	}
	return (dst);
}

// #include <libc.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char dst[11] = "Hallo";
// 	char src[11] = "test343";
// 	char dst2[11] = "Hallo";
// 	char src2[11] = "test343";
// 	printf("%s\n", dst);
// 	printf("%s\n", src);
// 	ft_memmove(src, dst, 0);
// 	printf("%s\n", dst);
// 	printf("%s\n", src);
// 	printf("%s\n", dst2);
// 	printf("%s\n", src2);
// 	memmove(src2, dst2, 0);
// 	printf("%s\n", dst2);
// 	printf("%s\n", src2);
// 	return (0);
// }