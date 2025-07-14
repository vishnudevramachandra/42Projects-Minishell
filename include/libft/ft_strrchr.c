/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:05:45 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 15:40:43 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, char c)
{
	int	i;

	i = 0;
	while (*str)
	{
		str++;
		i++;
	}
	while (i >= 0)
	{
		if (*str == c)
			return ((char *)str);
		str--;
		i--;
	}
	if (c == '\0')
		return ((char *)str);
	return (NULL);
}

// #include <ctype.h>
// #include <stdio.h>
// #include <string.h>
// int	main(void)
// {
// 	char str[] = "Test";
// 	char c1 = 'T';
// 	char c2 = 'o';
// 	char c3 = 't';
// 	char c4 = '\0';

// 	printf("%c %s %s\n", c1, str, ft_strrchr(str, c1));
// 	printf("%c %s %s\n", c1, str, strrchr(str, c1));	
// 	printf("%c %s %s\n", c2, str, ft_strrchr(str, c2));
// 	printf("%c %s %s\n", c2, str, strrchr(str, c2));
// 	printf("%s %s\n", str, ft_strrchr(str, c3));
// 	printf("%s %s\n", str, ft_strrchr(str, c3));
// 	printf("%s %s\n", str, ft_strrchr(str, c4));
// 	printf("%s %s\n", str, strrchr(str, c4));
// 	return (0);
// }