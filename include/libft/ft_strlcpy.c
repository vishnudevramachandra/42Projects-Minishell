/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:52:41 by swied             #+#    #+#             */
/*   Updated: 2025/03/12 15:45:28 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	i;
	size_t			srclen;

	srclen = 0;
	i = 0;
	while (src[srclen] != '\0')
		srclen++;
	if (size > 0)
	{
		while (i < size - 1 && src[i] != '\0')
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (srclen);
}

// #include <stdio.h>
// #include <string.h>
// int	main()
// {
// 	char dest1[10];
// 	char dest2[10];

// 	printf("%ld\n", ft_strlcpy(dest1, "testtest", 6));
// 	printf("%ld\n", ft_strlcpy(dest2, "testtest", 6));
// 	printf("%s\n", dest1);	
// 	printf("%s\n", dest2);
// 	return (0);
// }