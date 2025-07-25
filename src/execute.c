/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/14 23:04:36 by swied             #+#    #+#             */
/*   Updated: 2025/07/25 19:22:14 by swied            ###   ########.fr       */
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
	execute_pipes(cmd_list, envp);
	return (0);
}

int	execute_cmd(t_cmd_node *cmd_node, char **envp)
{
	char	*path;

	if (!cmd_node || !cmd_node->cmd)
		return (0);
	path = get_correct_path(cmd_node->cmd[0], envp);
	if (!path)
		return (printf("Cmd not found\n"), 1);
	execve(path, cmd_node->cmd, envp);
	printf("Execve faild\n");
	exit(EXIT_FAILURE);
}
