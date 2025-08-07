/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:17:07 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/20 12:01:53 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	chr;

	len = ft_strlen(s);
	chr = (char)c;
	while (len > 0)
	{
		if (s[len] == chr)
			return ((char *)(s + len));
		len--;
	}
	if (s[len] == chr)
		return ((char *)(s + len));
	return (NULL);
}

// #include <string.h>
// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "bonjour";

// 	printf("strrchr: %p\n", strrchr(str, 's'));
// 	printf("ft_strrchar: %p\n", ft_strrchr(str, 's'));
// 	return (0);
// }