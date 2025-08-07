/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:45:29 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 18:10:20 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = count * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < total_size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

// #include <unistd.h>

// static void	print_calloc_memory_values(char *str, size_t count, size_t size)
// {
// 	if (!str)
// 		return ;
// 	write(1, str, count * size);
// 	write(1, "\n", 1);
// }

// int	main(void)
// {
// 	size_t	count = 10;
// 	size_t	size = 2;
// 	print_calloc_memory_values((char *)calloc(count, size), count, size);
// 	print_calloc_memory_values((char *)ft_calloc(count, size), count, size);
// 	return (0);
// }