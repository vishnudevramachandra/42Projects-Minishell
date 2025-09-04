/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:23:33 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 16:36:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return ;
}

// #include <stdio.h>
// #include <libc.h>
// #include <unistd.h>
// int	main(void)
// {
// 	char string[11] = "Hallotest1";
// 	char string2[11] = "Hallotest2";
// 	ft_bzero(string, 3);
// 	printf("%s\n", string);
// 	write(1, string, 11);
// 	bzero(string2, 3);
// 	write(1, string2, 11);
// 	printf("%s\n", string2);
// 	return (0);
// }