/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/14 23:54:59 by swied            ###   ########.fr       */
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
	return (NULL);
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
	if (!result)
		return (perror("Cmd not found"), NULL);
	else
		return (result);
}

int	execute(t_data *data, char **envp)
{
	pid_t	pid;
	char	*path;
	char	*args[3];

	data->cmd = "ls";
	data->env = "-la";
	path = get_correct_path(data->cmd, envp);
	if (!path)
		return(printf("Cmd not found\n"), 0);
	args[0] = data->cmd;
	args[1] = data->env;
	args[2] = NULL;
	pid = fork();
	if (pid == -1)
		return(printf("Fork failed\n"), 1);
	if (pid == 0)
	{
		execve(path, args, envp);
		return (printf("Execve failed\n"), 1);
	}
	waitpid(pid, NULL, 0);
	free(path);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	(void)argc;
	(void)argv;
	
	data = malloc(sizeof(t_data));
	if (!data)
		return(printf("Malloc failed\n"), 1);
	execute(data, envp);
	free(data);
	return (0);
}
