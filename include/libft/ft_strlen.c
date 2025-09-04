/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 13:37:40 by swied             #+#    #+#             */
/*   Updated: 2025/03/11 11:43:46 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

// #include <stdio.h>
// #include <string.h>
// int	main()
// {
// 	printf("%ld\n", strlen("hallo"));
// 	printf("%ld", ft_strlen("hallo"));
// 	return(0);
// }