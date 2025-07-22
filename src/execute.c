/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/17 17:57:15 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_cmd_or_builtin(t_cmd_node *cmd_node, char **envp)
{
	if (cmd_node->cmd_type == 1)
		execute_builtin(cmd_node, envp);
	else
		execute_cmd(cmd_node, envp);
	//clean_up();
	return (0);
}

int	execute_cmd_loop(t_cmd_node *cmd_node, char **envp)
{
	execute_cmd_or_builtin(cmd_node, envp);
	return (0);
}

int	execute_loop(t_cmd_list *cmd_list, char **envp)
{
	t_cmd_node	*cmd_node;

	cmd_node = cmd_list->head;
	while (cmd_node)
	{
		if (execute_cmd_loop(cmd_node, envp))
			return (1);
		cmd_node = cmd_node->next;
	}
	return (0);
}

int	execute_cmd(t_cmd_node *cmd_node, char **envp)
{
	pid_t	pid;
	char	*path;

	if (!cmd_node || !cmd_node->cmd)
		return(0);
	path = get_correct_path(cmd_node->cmd[0], envp);
	if (!path)
		return(printf("Cmd not found\n"), 0);
	pid = fork();
	if (pid == -1)
		return(printf("Fork failed\n"), 1);
	if (pid == 0)
	{
		if (cmd_node->file->fd_infile != -1)
		{
			if (dup2(cmd_node->file->fd_infile, STDIN_FILENO) == -1)
			{
				perror("dup2 infile");
				exit(EXIT_FAILURE);
			}
		}
		if (cmd_node->file->fd_outfile != -1)
		{
			if (dup2(cmd_node->file->fd_outfile, STDOUT_FILENO) == -1)
			{
				perror ("dup2 outfile");
				exit(EXIT_FAILURE);
			}
		}
		execve(path, cmd_node->cmd, envp);
		printf("Execve failed\n%s | %s\n", cmd_node->cmd[0], cmd_node->cmd[1]);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	free(path);
	return (0);
}

void	cmd_init(t_cmd_node *cmd_node)
{
	cmd_node->cmd = malloc(sizeof(char *) * 3);
	cmd_node->cmd[0] = "ls";
	cmd_node->cmd[1] = "-l";
	cmd_node->cmd[2] = NULL;
	cmd_node->cmd_type = 0;
	// Datei-Redirect vorbereiten
	cmd_node->file = malloc(sizeof(t_file_list));
	cmd_node->file->size = 1;
	cmd_node->file->fd_infile = -1;
	cmd_node->file->fd_outfile = -1;
	// Datei-Node anlegen
	t_file_node *file_node = malloc(sizeof(t_file_node));
	file_node->filename = "test.txt";
	file_node->redir_type = REDIR_OUT;
	file_node->next = NULL;

	cmd_node->file->head = file_node;
	cmd_node->file->tail = file_node;
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

	t_cmd_list	*cmd_list = malloc(sizeof(t_cmd_list));
	t_cmd_node	*cmd_node = malloc(sizeof(t_cmd_node));

	cmd_init(cmd_node);

	cmd_list->head = cmd_node;
	cmd_list->tail = cmd_node;
	cmd_list->size = 1;

	// Redirects ausführen
	if (redirect(cmd_list) != 0)
		return (1);
	// Befehl ausführen
	execute_loop(cmd_list, envp);
	(void)envp;

	return (0);
}


// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	t_cmd	*cmd;
// 	if (!argv[1])
// 		return (0);
// 	cmd = malloc(sizeof(t_cmd));
// 	cmd->args = &argv[1];
// 	execute_cmd(cmd, envp);
// 	return (0);
// }

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
