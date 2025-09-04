/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 13:14:54 by swied             #+#    #+#             */
/*   Updated: 2025/03/12 13:27:44 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s2;

	i = 0;
	while (s1[i] != '\0')
		i++;
	i++;
	s2 = malloc(i * sizeof(char));
	if (!s2)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		s2[i] = s1[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*original = "Hallo, Welt!";
// 	char		*kopie;

// 	kopie = ft_strdup(original);
// 	printf("Original: %s\n", original);
// 	printf("Kopie:    %s\n", kopie);

// 	free(kopie);
// 	return (0);
// }
