/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:01:48 by swied             #+#    #+#             */
/*   Updated: 2025/03/21 14:21:26 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

size_t	ft_nlen(char const *s, size_t start, char c)
{
	size_t	count;

	count = 0;
	while (s[start + count] != '\0' && s[start + count] != c)
		count++;
	return (count);
}

size_t	ft_n_words(char const *s, char c)
{
	size_t	n_words;
	size_t	i;

	n_words = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && i == 0)
		{
			n_words++;
			i = 1;
		}
		else if (*s == c)
			i = 0;
		s++;
	}
	return (n_words);
}

char	**free_words(char **bigarray, int i)
{
	while (i >= 0)
	{
		free (bigarray[i]);
		i--;
	}
	free (bigarray);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**bigarray;
	size_t	i;
	size_t	j;
	size_t	word_len;

	i = 0;
	j = 0;
	bigarray = ft_calloc(ft_n_words(s, c) + 1, sizeof(char *));
	if (!bigarray)
		return (NULL);
	while (s[i] && j < ft_n_words(s, c))
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			word_len = ft_nlen(s, i, c);
			bigarray[j++] = ft_substr(s, i, word_len);
			if (!bigarray[j -1])
				return (free_words(bigarray, j -2));
			i += word_len;
		}
	}
	bigarray[j] = 0;
	return (bigarray);
}

// #include <stdlib.h>
// #include <stdio.h>

// int main(void)
// {
//     char *str = "Hello world this is a test";
//     char delimiter = ' ';
//     char **result = ft_split(str, delimiter);

//     if (!result)
//     {
//         printf("Fehler: ft_split hat NULL zurückgegeben.\n");
//         return (1);
//     }

//     int i = 0;
//     while (result[i])
//     {
//         printf("Wort %d: %s\n", i, result[i]);
//         free(result[i]);
//         i++;
//     }

//     free(result);
//     return (0);
// }
