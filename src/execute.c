/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/16 18:51:02 by swied            ###   ########.fr       */
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
		return (printf("Cmd not found\n"), NULL);
	else
		return (result);
}

int	execute(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	char	*path;

	path = get_correct_path(cmd->args[0], envp);
	if (!path)
		return(printf("Cmd not found\n"), 0);
	pid = fork();
	if (pid == -1)
		return(printf("Fork failed\n"), 1);
	if (pid == 0)
	{
		execve(path, cmd->args, envp);
		perror("Execve failed");
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free(path);
	return (0);
}

// int main(int argc, char **argv, char **envp)
// {
// 	t_cmd *cmd;
// 	(void)argc;
// 	(void)argv;
	
// 	printf("=== Testing pwd ===\n");
// 	builtin_pwd();
	
// 	printf("=== Testing echo ===\n");
// 	char *echo_args[] = {"echo", "hello", "world", NULL};
// 	builtin_echo(echo_args);
	
// 	printf("=== Testing echo -n ===\n");
// 	char *echo_n_args[] = {"echo", "-n", "test", "hallo", NULL};
// 	builtin_echo(echo_n_args);
	
// 	printf("=== Testing external command ===\n");
// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return 1;
// 	add_to_garbage(cmd);
// 	cmd->args = ft_split("ls -la", ' ');
// 	add_to_garbage(cmd->args);
// 	execute(cmd, envp);
	
// 	free_all_garbage();
// 	return 0;
// }

// Test main for builtin cd
// int	main(int argc, char **argv, char **envp)
// {
// 	char	*test_args[3];
// 	int		result;
// 	char	*cwd;
	
// 	(void)argc;
// 	(void)argv;

// 	printf("Start env:\n%s\nOld pwd:\n%s\n", getenv("PWD"), getenv("OLDPWD"));
// 	printf("Test 1: cd (no argument)\n");
// 	test_args[0] = "cd";
// 	test_args[1] = NULL;
// 	result = builtin_cd(test_args, &envp);
// 	cwd = getcwd(NULL, 0);
// 	printf("%s\n", cwd);
// 	printf("After Test 1 env:\n%s\nOld pwd:\n%s\n", getenv("PWD"), getenv("OLDPWD"));

// 	printf("Test 2: cd ..\n");
// 	test_args[0] = "cd";
// 	test_args[1] = "..";
// 	test_args[2] = NULL;
// 	result = builtin_cd(test_args, &envp);
// 	cwd = getcwd(NULL, 0);
// 	printf("%s\n", cwd);
// 	printf("After Test 2 env:\n%s\nOld pwd:\n%s\n", getenv("PWD"), getenv("OLDPWD"));

// 	printf("Test 3: cd /bin\n");
// 	test_args[0] = "cd";
// 	test_args[1] = "/bin";
// 	test_args[2] = NULL;
// 	result = builtin_cd(test_args, &envp);
// 	cwd = getcwd(NULL, 0);
// 	printf("%s\n", cwd);
// 	printf("After Test 3 env:\n%s\nOld pwd:\n%s\n", getenv("PWD"), getenv("OLDPWD"));
// 	return (0);
// }
