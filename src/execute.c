/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/29 00:29:32 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_cmd_or_builtin(t_cmd_node *cmd_node, char **envp)
{
	int	status;

	if (cmd_node->cmd_type == 1)
	{
		status = execute_builtin(cmd_node, envp);
		exit(status);
	}
	else
		execute_cmd(cmd_node, envp);
	return (1);
}

int	execute_cmd_loop(t_cmd_node *cmd_node, char **envp)
{
	execute_cmd_or_builtin(cmd_node, envp);
	return (0);
}

int	execute_loop(t_cmd_list *cmd_list, char **envp)
{
	execute_pipes(cmd_list, envp);
	return (0);
}

int	execute_cmd(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	if (!cmd_node || !cmd_node->cmd)
		exit(127);
	path = get_correct_path(cmd_node->cmd[0], envp);
	if (!path)
	{
		ft_putstr_fd("Command not found: \n", 2);
		ft_putendl_fd(cmd_node->cmd[0], 2);
		exit(127);
	}
	execve(path, cmd_node->cmd, envp);
	ft_putstr_fd("execve failed: ", 2);
	exit(126);
}
