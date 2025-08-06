/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:19:52 by swied             #+#    #+#             */
/*   Updated: 2025/08/06 19:43:54 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* creates pipefd and pid | pipes pipefd | forks pid | In child process setup the pipes, redirects and execute the cmd | In main process close the pipes and at end wait for every child process */
int	execute_pipes(t_cmd_list *cmd_list, t_env_list *env_list)
{
	pid_t		pid;
	int			i;
	int			status;
	int			pipefd[2];
	t_cmd_node	*current;

	current = cmd_list->head;
	cmd_list->prev_fd = -1;
	i = 0;
	while ((i < cmd_list->size) && (current))
	{
		if (i < (cmd_list->size - 1))
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			setup_pipes(cmd_list, pipefd, i);
			if (redirect(current) != 0)
				exit(EXIT_FAILURE);
			if (execute_cmd_or_builtin(current, env_list) != 0)
				exit(EXIT_FAILURE);
		}
		else
			close_pipes(cmd_list, current, pipefd, i);
		i++;
		current = current->next;
	}
	while (wait(&status) > 0);
	return (status);
}

/* If there is a prev_fd before -> close it and dup2 into standard */ 
void	setup_pipes(t_cmd_list *cmd_list, int *pipefd, int i)
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
}

/* If prev_fd is there close it | Also close after last cmd */
void	close_pipes(t_cmd_list *cmd_list, t_cmd_node *current,
	int *pipefd, int i)
{
	if (cmd_list->prev_fd != -1)
		close(cmd_list->prev_fd);
	if (i < cmd_list->size - 1)
	{
		close(pipefd[1]);
		cmd_list->prev_fd = pipefd[0];
	}
	if (current->file)
	{
		if (current->file->fd_infile != -1)
			close(current->file->fd_infile);
		if (current->file->fd_outfile != -1)
			close(current->file->fd_outfile);
	}
}
