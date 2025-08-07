/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:23:59 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/13 11:03:47 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i])
	{
		j = 0;
		while (needle[j] && (i + j) < len)
		{
			if (haystack[i + j] != needle[j])
				break ;
			j++;
		}
		if (!needle[j])
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	haystack[] = "There in lies the problem";
// 	char	needle[]= "problem";

// 	printf("strnstr: %s\n", strnstr(haystack,needle, 27));
// 	printf("ft_strnstr: %s\n", ft_strnstr(haystack, needle, 27));
// 	return (0);
// }