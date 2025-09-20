/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:44:50 by swied             #+#    #+#             */
/*   Updated: 2025/09/20 02:51:24 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Searches for PATH in envp and returns the value of it */
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

/* Helper function to free path array completely */
static void	free_path_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

/* Joins the suffix to the path | checks for access of the path */
char	*get_correct_path_second(char **path_array, char *suffix)
{
	int		i;
	char	*full_path;
	char	*result;

	i = 0;
	result = NULL;
	while (path_array[i])
	{
		full_path = ft_strjoin(path_array[i], suffix);
		if (!full_path)
			break ;
		if (access(full_path, X_OK) == 0)
			result = ft_strdup(full_path);
		free(full_path);
		if (result)
			break ;
		i++;
	}
	free_path_array(path_array);
	free(suffix);
	return (result);
}

/* gets the total path, creates suffix and splits the path it with ':' */
char	*get_correct_path(char *cmd, char **envp)
{
	char	**path_array;
	char	*suffix;
	char	*correct_path;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	correct_path = get_total_path(envp);
	if (!correct_path)
		return (NULL);
	suffix = ft_strjoin("/", cmd);
	if (!suffix)
		return (NULL);
	path_array = ft_split(correct_path, ':');
	if (!path_array)
	{
		free(suffix);
		return (NULL);
	}
	return (get_correct_path_second(path_array, suffix));
}
