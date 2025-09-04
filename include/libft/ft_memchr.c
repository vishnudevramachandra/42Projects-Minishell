/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:14:09 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 16:24:15 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	chr;
	unsigned char	*string;
	size_t			i;

	i = 0;
	chr = (unsigned char)c;
	string = (unsigned char *)str;
	while (i < n)
	{
		if (string[i] == chr)
			return ((void *)&string[i]);
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "/|\x12\xff\x09\0\x42\042\0\42|\\";
// 	char c1 = 'T';
// 	char c2 = 'o';
// 	char c3 = 's';
// 	char c4 = '\0';

// 	printf("%c %s %s\n", c1, str, ft_memchr(str, c1, 12));
// 	printf("%c %s %s\n", c1, str, memchr(str, c1, 3));
// 	printf("%c %s %s\n", c2, str, ft_memchr(str, c2, 12));
// 	printf("%c %s %s\n", c2, str, memchr(str, c2, 3));
// 	printf("%c %s %s\n", c3, str, ft_memchr(str, c3, 12));
// 	printf("%c %s %s\n", c3, str, memchr(str, c3, 3));
// 	printf("%c %s %s\n", c4, str, ft_memchr(str, c4, 12));
// 	printf("%c %s %s\n", c4, str, memchr(str, c4, 12));
// 	return (0);
// }