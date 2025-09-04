/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:37:37 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 16:47:41 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*newsrc;
	size_t			i;

	if (dst == src || n == 0)
		return (dst);
	ptr = (unsigned char *)dst;
	newsrc = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		ptr[i] = newsrc[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>
// #include <libc.h>
// int	main(void)
// {
// 	char dst[11] = "hallo";
// 	char src[11] = "hallo";
// 	char dst2[11] = "hallo";
// 	char src2[11] = "hallo";
// 	printf("%s\n", dst);
// 	ft_memcpy(dst, src, 0);
// 	printf("%s\n", dst);
// 	printf("%s\n", dst2);
// 	memcpy(dst2, src2, 0);
// 	printf("%s\n", dst2);
// 	return (0);
// }