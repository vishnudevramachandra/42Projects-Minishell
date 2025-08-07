/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:32:31 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/17 17:50:43 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (*str)
	{
		len++;
		str++;
	}
	return (len);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "yippie ho";

// 	printf("strlen: %lu\n", strlen(str));
// 	printf("ft_strlen: %lu\n", ft_strlen(str));
// 	return (0);
// }