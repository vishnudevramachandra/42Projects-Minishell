/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:05:55 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/25 10:49:44 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static size_t	nbr_of_splits(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s)
	{
		if (!*s)
			break ;
		if (*s != c)
		{
			i++;
			s = ft_strchr(s, c);
		}
		else
			s++;
	}
	return (i);
}

static size_t	substr_len(char const *s, char c)
{
	char	*ptr;

	ptr = ft_strchr(s, c);
	if (ptr)
		return (ptr - s);
	return (ft_strlen(s));
}

static void	deallocate_array(void **ptr, size_t size)
{
	while (size > 0)
	{
		size--;
		free(ptr[size]);
	}
	free(ptr);
}

static char	**ft_split_subfcn(
	char **str_arr, size_t size, char const *s, char c)
{
	size_t			len;
	size_t			i;
	unsigned int	start;

	i = 0;
	start = 0;
	while (i < size)
	{
		while (s[start] == c)
			start++;
		len = substr_len(&s[start], c);
		str_arr[i] = ft_substr(s, start, len);
		if (!str_arr[i])
		{
			deallocate_array((void **)str_arr, i);
			return (NULL);
		}
		start += len + 1;
		i++;
	}
	str_arr[i] = NULL;
	return (str_arr);
}

char	**ft_split(char const *s, char c)
{
	char	**str_arr;
	size_t	size;

	size = nbr_of_splits(s, c);
	str_arr = (char **)malloc((size + 1) * sizeof(char *));
	if (!str_arr)
		return (str_arr);
	return (ft_split_subfcn(str_arr, size, s, c));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = ",one,two,,three,";
// 	char	c = '-';
// 	char	**arr;
// 	size_t	i;

// 	arr = ft_split(str, c);
// 	i = 0;
// 	while (arr[i])
// 	{
// 		printf("%s\n", arr[i]);
// 		i++;
// 	}
// 	while (i > 0)
// 	{
// 		i--;
// 		free(arr[i]);
// 	}
// 	return (0);
// }