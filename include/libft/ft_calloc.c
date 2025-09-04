/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:37:22 by swied             #+#    #+#             */
/*   Updated: 2025/03/18 16:27:47 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

// #include <stdio.h>

// int main(void)
// {
//     size_t count = 5;
//     size_t size = sizeof(int);
//     int *arr;

//     arr = (int *)ft_calloc(count, size);
//     printf("Array nach ft_calloc():\n");
//     for (size_t i = 0; i < count; i++)
//         printf("%d ", arr[i]);

//     free(arr);
//     return (0);
// }