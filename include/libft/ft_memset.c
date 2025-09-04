/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:49:30 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 16:05:54 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;
	unsigned char	c2;
	size_t			i;

	ptr = (unsigned char *)b;
	c2 = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		ptr[i] = c2;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <libc.h>
// int	main(void)
// {
// 	char *string[10];
// 	printf("%s\n", ft_memset(string, 'a', 5));
// 	printf("%s", memset(string, 'a', 5));
// 	return (0);
// }