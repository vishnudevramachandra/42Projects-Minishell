/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:06:05 by vramacha          #+#    #+#             */
/*   Updated: 2025/05/23 11:05:12 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	if (dstsize < dst_len)
		i = dstsize;
	else
		i = dst_len;
	while ((i + 1) < dstsize && *src)
	{
		dst[i] = *src;
		src++;
		i++;
	}
	if (i >= dst_len)
		dst[i] = '\0';
	while (*src)
	{
		src++;
		i++;
	}
	return (i);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	str1[] = " alone";
// 	char	str2[13] = "home";
// 	char	str3[13] = "home";
// 	size_t	len;

// 	len = strlcat(str2, str1, 13);
// 	printf("strlcat: %s, special len: %lu\n", str2, len);
// 	len = ft_strlcat(str3, str1, 13);
// 	printf("ft_strlcpy: %s, special len: %lu\n", str3, len);
// 	return (0);
// }