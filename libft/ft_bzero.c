/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:32:39 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/20 12:08:07 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *)s)[i] = 0;
		i++;
	}
}

// #include <strings.h>
// #include <stdio.h>

// static void	print_zero_appended_string(char *str)
// {
// 	int	i = 0;
// 	if (!str[i])
// 		printf("0");
// 	else
// 		printf("%s\n", str + i);
// 	while (!str[i])
// 	{
// 		i++;
// 		if (!str[i])
// 			printf("0");
// 		else
// 			printf("%s\n", str + i);
// 	}
// }

// int	main(void)
// {
// 	char	str[13] = "home alone"; 
// 	bzero(str, 2);
// 	print_zero_appended_string(str);
// 	ft_bzero(str, 4);
// 	print_zero_appended_string(str);
// 	return (0);
// }