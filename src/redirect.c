#include "../include/execute.h"

int open_redirects(t_cmd_node *cmd_node)
{
	t_file_node *current;
	current = cmd_node->file->head;
	check_fd(cmd_node);
	while (current)
	{
		if (current->redir_type == REDIR_IN)
		{
			cmd_node->file->fd_infile = open(current->filename, O_RDONLY);
			if (cmd_node->file->fd_infile == -1)
				return (perror(current->filename), 1);
		}
		else if (current->redir_type == REDIR_OUT)
		{
			cmd_node->file->fd_outfile = open(current->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			if (cmd_node->file->fd_outfile == -1)
				return (perror(current->filename), 1);
		}
		else if (current->redir_type == REDIR_APPEND)
		{
			cmd_node->file->fd_outfile = open(current->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			if (cmd_node->file->fd_outfile == -1)
				return (perror(current->filename), 1);
		}
		current = current->next;
	}
	return (0);
}

void	check_fd(t_cmd_node *cmd_node)
{
	if (cmd_node->file->fd_infile != -1)
	{
		close(cmd_node->file->fd_infile);
		cmd_node->file->fd_infile = -1;
	}
	if (cmd_node->file->fd_outfile != -1)
	{
		close(cmd_node->file->fd_outfile);
		cmd_node->file->fd_outfile = -1;
	}
}

int redirect(t_cmd_node *cmd_node)
{
	if (!cmd_node || !cmd_node->file || !cmd_node->file->head)
		return (0);
	if (open_redirects(cmd_node) != 0)
		return (1);
	if (cmd_node->file->fd_infile != -1)
	{
		dup2(cmd_node->file->fd_infile, STDIN_FILENO);
		close(cmd_node->file->fd_infile);
	}
	if (cmd_node->file->fd_outfile != -1)
	{
		dup2(cmd_node->file->fd_outfile, STDOUT_FILENO);
		close(cmd_node->file->fd_outfile);
	}
	return (0);
}