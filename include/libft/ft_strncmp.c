/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:16:05 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 16:20:00 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	i;

	i = 1;
	if (size == 0)
		return (0);
	while (size > i)
	{
		if (*s1 == '\0' || *s2 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		else if (*s1 == *s2)
		{
			s1++;
			s2++;
		}
		else
			return ((unsigned char)*s1 - (unsigned char)*s2);
		i++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

// #include <string.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char s1[] = "test\200f";
// 	char s2[] = "test\0f";
// 	printf("%d\n", ft_strncmp(s1, s2, 6));
// 	printf("%d\n", strncmp(s1, s2, 6));
// 	return(0);
// }