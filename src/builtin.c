/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 15:53:58 by swied             #+#    #+#             */
/*   Updated: 2025/07/26 16:34:27 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_builtin(t_cmd_node *cmd_node, char **envp)
{
	if (ft_strcmp(cmd_node->cmd[0], "cd") == 0)
		return (builtin_cd(cmd_node->cmd, &envp), 0);
	else if (ft_strcmp(cmd_node->cmd[0], "pwd") == 0)
		return (builtin_pwd(), 0);
	else if (ft_strcmp(cmd_node->cmd[0], "echo") == 0)
		return (builtin_echo(cmd_node->cmd), 0);
	else if (ft_strcmp(cmd_node->cmd[0], "env") == 0)
		return (builtin_env(envp), 0);
	return (1);
}
