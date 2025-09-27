/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/09/28 01:07:21 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* if cmd_type 1 executes builtin | if cmd_type 0 executes cmd */
int	execute_cmd_or_builtin(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int	status;

	status = 0;
	if (cmd_node->cmd_type == 1)
	{
		status = execute_builtin(cmd_node, env_list);
		exit(status);
	}
	else
	{
		status = execute_cmd(cmd_node, env_list);
		exit(status);
	}
	return (1);
}

static int	close_backups(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
		close(stdin_backup);
	if (stdout_backup != -1)
		close(stdout_backup);
	return (1);
}

/* if only one cmd and its a builtin, then execute in main process |
else execute pipes */
int	execute_loop(t_cmd_list *cmd_list, t_env_list *env_list)
{
	int	status;
	int	stdin_backup;
	int	stdout_backup;

	if (handle_cmd_list_heredocs(cmd_list, env_list) == -1)
		return (1);
	if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
	{
		stdin_backup = dup(STDIN_FILENO);
		stdout_backup = dup(STDOUT_FILENO);
		if (stdin_backup == -1 || stdout_backup == -1)
			return (close_backups(stdin_backup, stdout_backup), 1);
		setup_pipes(cmd_list, STDIN_FILENO, 0);
		if (redirect(cmd_list->head) != 0)
			status = 1;
		else
			status = execute_builtin(cmd_list->head, env_list);
		dup2(stdin_backup, STDIN_FILENO);
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdin_backup);
		close(stdout_backup);
	}
	else
		status = execute_pipes(cmd_list, env_list);
	return (status);
}

/* creates **new_envp which get filled with list_to_dblarray |
gets cmd path from get_correct_path | executes cmd with execve */
int	execute_cmd(t_cmd_node *cmd_node, t_env_list *env_list)
{
	char	*path;
	char	**new_envp;

	if (!cmd_node || !cmd_node->cmd)
		exit(127);
	new_envp = list_to_dblarray(env_list);
	path = get_correct_path(cmd_node->cmd[0], new_envp);
	if (!path)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd_node->cmd[0], 2);
		exit(127);
	}
	execve(path, cmd_node->cmd, new_envp);
	free(path);
	free_all_garbage();
	ft_putstr_fd("execve failed: ", 2);
	exit(126);
}
