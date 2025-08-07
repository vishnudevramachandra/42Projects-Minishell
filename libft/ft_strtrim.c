/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:58:05 by vramacha          #+#    #+#             */
/*   Updated: 2025/03/24 18:01:38 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static char	*str_beg_trim_loc(char const *s1, char const *set)
{
	size_t	i;

	while (*s1)
	{
		i = 0;
		while (set[i])
		{
			if (*s1 != set[i])
				i++;
			else
				break ;
		}
		if (!set[i])
			break ;
		s1++;
	}
	return ((char *)s1);
}

static char	*str_end_trim_loc(char const *s1, char const *set, char	*beg_ptr)
{
	size_t	i;

	while (*s1)
		s1++;
	s1--;
	while (s1 != beg_ptr)
	{
		i = 0;
		while (set[i])
		{
			if (*s1 != set[i])
				i++;
			else
				break ;
		}
		if (!set[i])
			break ;
		s1--;
	}
	return ((char *)s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*beg_ptr;
	char	*end_ptr;
	char	*trim_str;
	size_t	len;

	if (!*s1)
		return (ft_strdup(s1));
	beg_ptr = str_beg_trim_loc(s1, set);
	if (!*beg_ptr)
		return (ft_strdup(beg_ptr));
	end_ptr = str_end_trim_loc(s1, set, beg_ptr);
	len = (end_ptr - beg_ptr) + 2;
	trim_str = (char *)malloc(len * sizeof(char));
	if (!trim_str)
		return (NULL);
	ft_strlcpy(trim_str, beg_ptr, len);
	return (trim_str);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	*str = "lorem ipsum dolor sit amet";
// 	char	*set = "l ";
// 	char	*ptr;

// 	ptr = ft_strtrim(str, set);
// 	printf("ft_strtrim: %s\n", ptr);
// 	free(ptr);
// 	return (0);
// }