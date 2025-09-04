/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_basicfcns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:43:42 by vramacha          #+#    #+#             */
/*   Updated: 2025/08/27 17:18:56 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft/libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(charset, s[i]))
			break ;
		i++;
	}
	return (i);
}

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]))
			break ;
		i++;
	}
	return (i);
}

size_t	match_nums(
	const char *s1, const char *s2, size_t len, int flag)
{
	size_t	i;

	i = 0;
	if (flag < 1)
	{
		while (s1[i])
		{
			if (ft_strchr(s2, s1[i]))
				len++;
			i++;
		}
	}
	else
	{
		while (s1[i])
		{
			if (ft_strchr(s2, s1[i]))
				len--;
			i++;
		}
	}
	return (len);
}

/* calculate the intersection of sets (s1 & s2) */
char	*set_inter(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = match_nums(s1, s2, 0, 0);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (*s1)
	{
		if (ft_strchr(s2, *s1))
		{
			s[i] = *s1;
			i++;
		}
		s1++;
	}
	s[i] = 0;
	return (s);
}

/* calculate the difference of sets (s1 - s2) */
char	*set_diff(const char *s1, const char *s2)
{
	size_t	len;
	size_t	i;
	char	*s;

	len = match_nums(s1, s2, ft_strlen(s1), 1);
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	i = 0;
	while (*s1)
	{
		if (!ft_strchr(s2, *s1))
		{
			s[i] = *s1;
			i++;
		}
		s1++;
	}
	s[i] = 0;
	return (s);
}
