/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:19:52 by swied             #+#    #+#             */
/*   Updated: 2025/07/24 19:28:59 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	execute_pipes(t_cmd_list *cmd_list, char **envp)
{
	int	i;
	pid_t	pid;
	int		status;
	int		pipefd[2];
	t_cmd_node	*current;

	current = cmd_list->head;
	i = 0;
	cmd_list->prev_fd = -1;
	while (i < cmd_list->size && current)
	{
		if (i < cmd_list->size - 1)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			if (cmd_list->prev_fd != -1)
			{
				dup2(cmd_list->prev_fd, STDIN_FILENO);
				close(cmd_list->prev_fd);
			}
			if (i < cmd_list->size - 1)
			{
				close(pipefd[0]);
				dup2(pipefd[1], STDOUT_FILENO);
				close(pipefd[1]);
			}
			if (execute_cmd_or_builtin(current, envp))
				exit(EXIT_FAILURE);
		}
		else
		{
			if (cmd_list->prev_fd != -1)
				close(cmd_list->prev_fd);
			if (i < cmd_list->size - 1)
			{
				close(pipefd[1]);
				cmd_list->prev_fd = pipefd[0];
			}
		}
		i++;
		current = current->next;
	}
	while (wait(&status) > 0);
	return (status);
}
