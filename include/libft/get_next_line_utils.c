/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 16:42:43 by swied             #+#    #+#             */
/*   Updated: 2025/07/31 18:49:39 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// size_t	ft_strlcpy(char *dest, const char *src, unsigned int size)
// {
// 	unsigned int	i;
// 	size_t			srclen;

// 	srclen = 0;
// 	i = 0;
// 	while (src[srclen] != '\0')
// 		srclen++;
// 	if (size > 0)
// 	{
// 		while (i < size - 1 && src[i] != '\0')
// 		{
// 			dest[i] = src[i];
// 			i++;
// 		}
// 		dest[i] = '\0';
// 	}
// 	return (srclen);
// }

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
	{
		if (s[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	char	*str;
	size_t	strlen;

	strlen = ft_strlen_gnl(s1) + ft_strlen_gnl(s2);
	str = malloc((strlen + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ft_strlen_gnl(s1) + 1);
	ft_strlcpy(str + ft_strlen_gnl(s1), s2, ft_strlen_gnl(s2) + 1);
	return (str);
}

void	delete_buff(char *buff)
{
	int	i;
	int	buff_count;
	int	j;

	i = 0;
	buff_count = 0;
	while (buff[buff_count] != '\0')
		buff_count++;
	j = ft_strlen_gnl(buff);
	while (i < buff_count)
	{
		if (j + i < buff_count)
		{
			buff[i] = buff[j + i];
			buff[j + i] = '\0';
		}
		else
			buff[i] = '\0';
		i++;
	}
}

char	*free_line(char *new_line)
{
	if (new_line)
		free(new_line);
	return (NULL);
}
