/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:44:50 by swied             #+#    #+#             */
/*   Updated: 2025/08/03 12:08:56 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

char	*get_total_path(char **envp)
{
	char	*correct_path;
	int		i;

	correct_path = NULL;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			correct_path = envp[i] + 5;
			break ;
		}
		i++;
	}
	return (correct_path);
}

char	*get_correct_path_second(char **path_array, char *suffix)
{
	int		i;
	char	*result;

	i = 0;
	while (path_array[i])
	{
		result = ft_strjoin(path_array[i], suffix);
		free(path_array[i]);
		path_array[i] = result;
		if (path_array[i] == NULL)
			return (free(suffix), free(path_array), NULL);
		if (access(path_array[i], X_OK) == 0)
		{
			result = ft_strdup(path_array[i]);
			return (free(suffix), result);
		}
		i++;
	}
	return (free(suffix), free(path_array), free(result), NULL);
}

char	*get_correct_path(char *cmd, char **envp)
{
	char	**path_array;
	char	*suffix;
	char	*correct_path;
	char	*result;

	correct_path = get_total_path(envp);
	if (!correct_path)
		return (NULL);
	suffix = ft_strjoin("/", cmd);
	if (!suffix)
		return (NULL);
	path_array = ft_split(correct_path, ':');
	if (!path_array)
		return (free(suffix), NULL);
	result = get_correct_path_second(path_array, suffix);
	return (result);
}
