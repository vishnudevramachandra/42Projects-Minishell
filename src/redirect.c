/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 19:44:30 by swied             #+#    #+#             */
/*   Updated: 2025/09/11 12:47:40 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Open every redirect and set fd_infile or fd_outfile | Gets overwritten when multiple redirects */
int open_redirects(t_cmd_node *cmd_node)
{
	t_file_node *current;

	current = cmd_node->file_list->head;
	check_fd(cmd_node);
	while (current)
	{
		if (current->redir_type == REDIR_IN)
		{
			cmd_node->file_list->fd_infile = open(current->filename, O_RDONLY);
			if (cmd_node->file_list->fd_infile == -1)
				return (perror(current->filename), 1);
		}
		else if (current->redir_type == REDIR_OUT)
		{
			cmd_node->file_list->fd_outfile = open(current->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd_node->file_list->fd_outfile == -1)
				return (perror(current->filename), 1);
		}
		else if (current->redir_type == REDIR_APPEND)
		{
			cmd_node->file_list->fd_outfile = open(current->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (cmd_node->file_list->fd_outfile == -1)
				return (perror(current->filename), 1);
		}
		else if (current->redir_type == REDIR_HEREDOC)
			// cmd_node->file_list->fd_infile = create_heredoc_fd(cmd_node->hd_list->head);
			cmd_node->file_list->fd_infile = get_last_hd_fd(cmd_node);
		current = current->next;
	}
	return (0);
}

/* If there is a fd_infile or fd_outfile -> close it and set it to -1 (After one pipe done) */
void	check_fd(t_cmd_node *cmd_node)
{
	if (!cmd_node || !cmd_node->file_list)
		return ;
	if (cmd_node->file_list->fd_infile != -1)
	{
		close(cmd_node->file_list->fd_infile);
		cmd_node->file_list->fd_infile = -1;
	}
	if (cmd_node->file_list->fd_outfile != -1)
	{
		close(cmd_node->file_list->fd_outfile);
		cmd_node->file_list->fd_outfile = -1;
	}
}

/* Routine of redirects: Set fd_infile and fd_outfile with open_redirects | if its filled dup2 from STD_IN/STD_OUT to fd_infile/fd_outfile */
int redirect(t_cmd_node *cmd_node)
{
	if (!cmd_node || !cmd_node->file_list)
		return (0);
	if (open_redirects(cmd_node) != 0)
		return (1);
	if (cmd_node->file_list->fd_infile != -1)
	{
		dup2(cmd_node->file_list->fd_infile, STDIN_FILENO);
		close(cmd_node->file_list->fd_infile);
	}
	if (cmd_node->file_list->fd_outfile != -1)
	{
		dup2(cmd_node->file_list->fd_outfile, STDOUT_FILENO);
		close(cmd_node->file_list->fd_outfile);
	}
	return (0);
}

int	get_last_hd_fd(t_cmd_node *cmd_node)
{
	t_hd_node	*current;
	int			fd;

	if (!cmd_node || !cmd_node->hd_list || !cmd_node->hd_list->head)
		return (-1);
	current = cmd_node->hd_list->head;
	while (current->next)
		current = current->next;
	fd = create_heredoc_fd(current);
	return (fd);
}
