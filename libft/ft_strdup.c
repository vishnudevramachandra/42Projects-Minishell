/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:14:05 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 18:10:58 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dst;
	size_t	dstsize;

	dstsize = ft_strlen(src) + 1;
	dst = (char *)malloc(dstsize * sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, src, dstsize);
	return (dst);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*src = "home alone forever";
// 	char	*dst;

// 	dst = strdup(src);
// 	printf("%s\n", dst);
// 	free(dst);
// 	dst = ft_strdup(src);
// 	printf("%s\n", dst);
// 	free(dst);
// }