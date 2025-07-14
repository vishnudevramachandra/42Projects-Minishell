/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:00:01 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 13:42:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (1);
	return (0);
}

// #include <stdio.h>
// #include <ctype.h>
// int main()
// {
//     printf("%d\n", isalnum('a'));
//     printf("%d", ft_isalnum('a'));
//     return(0);
// }