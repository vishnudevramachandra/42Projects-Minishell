/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:24 by swied             #+#    #+#             */
/*   Updated: 2025/03/18 16:19:29 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_checkset(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (*s1 == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimstr;
	size_t	str_start;
	size_t	i_end;
	size_t	s1len;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	s1len = ft_strlen(s1);
	if (s1len == 0)
		return (ft_strdup(""));
	str_start = 0;
	i = s1len - 1;
	while (str_start < s1len && ft_checkset(s1 + str_start, set))
		str_start++;
	i_end = 0;
	while (i > str_start && ft_checkset(s1 + i, set))
	{
		i_end++;
		i--;
	}
	if (str_start >= s1len)
		return (ft_strdup(""));
	trimstr = ft_substr(s1, str_start, s1len - str_start - i_end);
	return (trimstr);
}

// #include <stdio.h>
// #include "libft.h"

// int main()
// {
//     char s1[] = "";
//     char set[] = "cdef";

//     char *trimmed_str = ft_strtrim(s1, set);
//     printf("Original String: '%s'\n", s1);
//     printf("Trimmed String: '%s'\n", trimmed_str);
// 	free(trimmed_str);
//     return 0;
// }