/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 17:46:35 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 19:33:43 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}

// #include <stdio.h>
// #include <ctype.h>
// int	main()
// {
// 	printf("%c\n", ft_tolower('A'));
// 	printf("%c", tolower('A'));
// 	return (0);
// }