/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:31:33 by swied             #+#    #+#             */
/*   Updated: 2025/03/17 19:31:30 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	strlen;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	if (start >= strlen)
		return (ft_strdup(""));
	if (len > strlen - start)
		len = strlen - start;
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s + start, len + 1);
	return (str);
}

// #include <stdio.h>

// int main()
// {
//     char *s = "Hallo, Welt!";
//     unsigned int start = 7;
//     size_t len = 5;

//     char *substr = ft_substr(s, start, len);
//     if (substr)
//     {
//         printf("Substring: %s\n", substr);
//         free(substr);
//     }
//     else
//     {
//         printf("Speicherzuweisung fehlgeschlagen!\n");
//     }

//     return 0;
// }