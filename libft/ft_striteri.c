/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:38:49 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/18 13:58:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;
	size_t			len;

	len = ft_strlen(s);
	i = 0;
	while (i < len)
	{
		f(i, &s[i]);
		i++;
	}
}

// #include <stdio.h>

// void	add_index(unsigned int i, char *c)
// {
// 	*c = *c + i;
// }

// int	main(void)
// {
// 	char	s[11] = "0000000000";

// 	ft_striteri(s, add_index);
// 	printf("%s\n", s);
// 	return (0);
// }