/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:13:30 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/19 14:55:53 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strchr(const char *s, int c)
{
	char	chr;

	chr = (char)c;
	if (*s == chr)
		return ((char *)s);
	while (*s)
	{
		s++;
		if (*s == chr)
			return ((char *)s);
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "Home alone";

// 	printf("strchr: %p\n", strchr(str, 'H' + 256));
// 	printf("ft_strchar: %p\n", ft_strchr(str, 'H' + 256));
// 	return (0);
// }