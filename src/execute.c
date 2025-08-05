/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 20:45:32 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

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

int	execute_loop(t_cmd_list *cmd_list, t_env_list *env_list)
{
	int	status;

	if (cmd_list->size == 1 && cmd_list->head->cmd_type == 1)
		status = execute_builtin(cmd_list->head, env_list);
	else
		status = execute_pipes(cmd_list, env_list);
	return (status);
}

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
	ft_putstr_fd("execve failed: ", 2);
	exit(126);
}
