/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:59:31 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/19 14:25:46 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	chr;

	chr = (unsigned char)c;
	while (n > 0)
	{
		if (*(unsigned char *)s == chr)
			return ((void *)s);
		s++;
		n--;
	}
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "Home Alonez";
// 	char	c = 'z';
// 	size_t	n = 10;

// 	printf("memchr: %p\n", memchr(str, c, n));
// 	printf("ft_memchr: %p\n", ft_memchr(str, c, n));
// 	return (0);
// }