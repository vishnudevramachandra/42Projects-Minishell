/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 18:20:30 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_cmd_or_builtin(t_cmd_node *cmd_node, char **envp,
	t_env_list *env_list)
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
		execute_cmd(cmd_node, envp, env_list);
		exit(status);
	}
	return (1);
}

int	execute_loop(t_cmd_list *cmd_list, char **envp, t_env_list *env_list)
{
	int	status;

	if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
	{
		status = execute_builtin(cmd_list->head, env_list);
		return (status);
	}
	execute_pipes(cmd_list, envp, env_list);
	return (0);
}

int	execute_cmd(t_cmd_node *cmd_node, char **envp, t_env_list *env_list)
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
	(void)env_list;
	execve(path, cmd_node->cmd, envp);
	free(path);
	ft_putstr_fd("execve failed: ", 2);
	exit(126);
}
