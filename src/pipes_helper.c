/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/20 16:22:46 by swied             #+#    #+#             */
/*   Updated: 2025/09/24 15:19:24 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

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
	if (current && current->file_list)
	{
		if (current->file_list->fd_infile != -1)
			close(current->file_list->fd_infile);
		if (current->file_list->fd_outfile != -1)
			close(current->file_list->fd_outfile);
	}
}
