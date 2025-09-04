/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:55:46 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 12:12:17 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	i;

	dest_len = 0;
	src_len = 0;
	i = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	while (src[src_len] != '\0')
		src_len++;
	if (dest_len == size)
		return (size + src_len);
	while (src[i] != '\0' && (dest_len + i) < (size - 1))
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < size)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

// #include <stdio.h>
// #include <string.h>
// int main()
// {
// 	char dest1[50] = "hallo";
// 	char dest2[50] = "hallo";
// 	char src[] = "test";
// 	printf("%ld\n", ft_strlcat(dest1, src, 3));
// 	printf("%s\n", dest1);
// 	printf("%ld\n", strlcat(dest2, src, 3));
// 	printf("%s\n", dest2);
// 	return (0);
// }
