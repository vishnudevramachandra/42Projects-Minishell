/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:51:06 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 12:18:41 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return ((char *)str);
		str++;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

// #include <string.h>
// #include <ctype.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char str[] = "Test";
// 	char c1 = 'T';
// 	char c2 = 'o';
// 	char c3 = 's';
// 	char c4 = '\0';

// 	printf("%c %s %s\n", c1, str, ft_strchr(str, c1));
// 	printf("%c %s %s\n", c1, str, strchr(str, c1));
// 	printf("%c %s %s\n", c2, str, ft_strchr(str, c2));
// 	printf("%c %s %s\n", c2, str, strchr(str, c2));
// 	printf("%c %s %s\n", c3, str, ft_strchr(str, c3));
// 	printf("%c %s %s\n", c3, str, strchr(str, c3));
// 	printf("%s %s\n", str, ft_strchr(str, c4));
// 	printf("%s %s\n", str, strchr(str, c4));
// 	return (0);
// }