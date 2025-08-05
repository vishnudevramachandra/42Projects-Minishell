/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:53:58 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 18:20:10 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_builtin(t_cmd_node *cmd_node, t_env_list *env_list)
{
	int	status;

	status = 0;
	if (ft_strcmp(cmd_node->cmd[0], "cd") == 0)
		status = builtin_cd(cmd_node->cmd, env_list);
	else if (ft_strcmp(cmd_node->cmd[0], "pwd") == 0)
		status = (builtin_pwd());
	else if (ft_strcmp(cmd_node->cmd[0], "echo") == 0)
		status = builtin_echo(cmd_node->cmd);
	else if (ft_strcmp(cmd_node->cmd[0], "env") == 0)
		status = builtin_env(env_list);
	else if (ft_strcmp(cmd_node->cmd[0], "exit") == 0)
		builtin_exit();
	else if (ft_strcmp(cmd_node->cmd[0], "export") == 0)
		builtin_export(env_list, cmd_node);
	return (status);
}
