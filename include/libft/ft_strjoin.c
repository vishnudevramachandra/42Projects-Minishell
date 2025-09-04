/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:34:47 by swied             #+#    #+#             */
/*   Updated: 2025/03/12 15:50:58 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	strlen;

	strlen = ft_strlen(s1) + ft_strlen(s2);
	str = malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcpy(str + ft_strlen(s1), s2, ft_strlen(s2) + 1);
	return (str);
}

// #include <stdio.h>

// int main(void)
// {
//     char *s1 = "Hallo, ";
//     char *s2 = "Welt!";
//     char *result;

//     result = ft_strjoin(s1, s2);
//     if (result)
//     {
//         printf("Ergebnis: %s\n", result);
//         free(result);
//     }
//     else
//     {
//         printf("Fehler: Speicher konnte nicht reserviert werden.\n");
//     }

//     return 0;
// }
