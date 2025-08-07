/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:31:20 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 18:46:48 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ptr;
	size_t			substr_len;

	if (start < ft_strlen(s))
	{
		substr_len = ft_strlen(s) - start;
		s += start;
	}
	else
		substr_len = 0;
	if (len < substr_len)
		substr_len = len;
	ptr = (char *)malloc((substr_len + 1) * sizeof(char));
	if (!ptr)
		return (ptr);
	ft_strlcpy(ptr, s, substr_len + 1);
	return (ptr);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "hola";
// 	char	*substr;

// 	substr = ft_substr(str, 0, 2);
// 	printf("ft_substr: %s\n", substr);
// 	free(substr);
// 	return (0);
// }