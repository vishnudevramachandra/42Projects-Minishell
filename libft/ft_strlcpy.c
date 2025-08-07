/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:24:20 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/11 16:05:39 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (dstsize > 1 && src[i])
	{
		dst[i] = src[i];
		i++;
		dstsize--;
	}
	if (dstsize >= 1)
		dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = "home";
// 	char	str2[11];
// 	size_t	len;

// 	len = strlcpy(str2, str1, 6);
// 	printf("strlcpy: %s, src len: %lu\n", str2, len);
// 	len = ft_strlcpy(str2, str1, 2);
// 	printf("ft_strlcpy: %s, src len: %lu\n", str2, len);
// 	return (0);
// }