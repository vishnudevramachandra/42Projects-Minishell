/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 17:39:33 by swied             #+#    #+#             */
/*   Updated: 2025/09/22 18:08:21 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* removes all quotes in delimiter */
static void	remove_quotes(char **delimiter, int count)
{
	int		i;
	int		j;
	char	*tmp;
	char	*del;

	i = 0;
	j = 0;
	del = delimiter[0];
	tmp = malloc(count * sizeof(char *) + 1);
	if (!tmp)
		return ;
	while (del[i])
	{
		if (del[i] != '\"' && del[i] != '\'')
		{
			tmp[j] = del[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	gc_free(del);
	delimiter[0] = ft_strdup(tmp);
	add_to_gc(delimiter[0]);
	return ;
}

/* checks if delimiter has quotes and returns the flag */
int	check_del_for_quotes(char **delimiter)
{
	int		i;
	int		flag;
	int		count;
	char	*del;

	i = 0;
	flag = 0;
	count = 0;
	del = delimiter[0];
	while (del[i])
	{
		if (del[i] == '\"' || del[i] == '\'')
		{
			flag = 1;
			count++;
		}
		i++;
	}
	if (flag)
		remove_quotes(delimiter, count);
	return (flag);
}
