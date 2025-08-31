/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:39:48 by swied             #+#    #+#             */
/*   Updated: 2025/09/01 00:39:03 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"
#include <unistd.h>
#include <fcntl.h>

/* collects heredoc input in child_process */
static int	collect_heredoc_in_child(char *delimiter,
	int write_fd)
{
	char	*line;
	// char	*expanded_line;

	// setup_heredoc_signals();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
		// if (g_signal_recieved == SIGINT)
			// return (free(line), close(write_fd), exit(130), 1);
		if (is_delimiter(line, delimiter))
			return(free(line), close(write_fd), exit(0), 0);
		// expanded_line = expand_heredoc(mini, line);
		// if (!expanded_line)
		// 	return (free(line), close(write_fd), exit(1), 1);
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		// free(expanded_line);
		free(line);
	}
	return (close(write_fd), exit(0), 0);
}

/* reads from the child process and stores the lines in the hd_node */
static int	read_from_child_and_store(t_hd_node *hd_node, int read_fd)
{
	char	*line;
	char	*processed_line;

	while (1)
	{
		line = get_next_line(read_fd);
		if (!line)
			break ;
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		processed_line = ft_strdup(line);
		if (!processed_line)
			return (free(line), -1);
		add_to_gc(processed_line);
		add_line_to_heredoc(hd_node, processed_line);
		free(line);
	}
	return (0);
}

/* creates a pipe and collects heredoc input in child_process */
static int	create_heredoc_with_child(char *delimiter,
	t_hd_node *hd_node)
{
	int		pipe_fd[2];
	pid_t	child_pid;
	int		status;

	if (pipe(pipe_fd) == -1)
		return (-1);
	child_pid = fork();
	if (child_pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (child_pid == 0)
	{
		close(pipe_fd[0]);
		collect_heredoc_in_child(delimiter, pipe_fd[1]);
	}
	else
	{
		close(pipe_fd[1]);
		if (read_from_child_and_store(hd_node, pipe_fd[0]) == -1)
			return (close(pipe_fd[0]), waitpid(child_pid, &status, 0), -1);
		close(pipe_fd[0]);
		return (0);
	}
	return (0);
}

/* allocates a new hd_node and gives it a limiter */
t_hd_node	*create_hd_node(char *lim)
{
	t_hd_node	*new;

	new = gc_malloc(sizeof(t_hd_node));
	if (!new)
		return (NULL);
	new->lines = NULL;
	new->lim = ft_strdup(lim);
	if (!new->lim)
		return (NULL);
	new->file_node = NULL;
	new->next = NULL;
	return (new);
}

/* creates a new hd_node and adds it to the cmd_node's hd_list */
int create_heredoc(char *lim, t_cmd_node *cmd_node, t_file_node *file_node)
{
	t_hd_node	*new_hd;

	new_hd = create_hd_node(lim);
	if (!new_hd)
		return (-1);
	new_hd->file_node = file_node;
	if (!cmd_node->hd_list->head)
	{
		cmd_node->hd_list->head = new_hd;
		cmd_node->hd_list->tail = new_hd;
		cmd_node->hd_list->size = 1;
	}
	else
	{
		cmd_node->hd_list->tail->next = new_hd;
		cmd_node->hd_list->tail = new_hd;
		cmd_node->hd_list->size++;
	}
	create_heredoc_with_child(lim, new_hd);
	return (0);
}

/* Processes all heredocs in the entire cmd_list */
int	process_heredocs_in_cmd_list(t_cmd_list *cmd_list)
{
	t_cmd_node	*current;

	if (!cmd_list || !cmd_list->head)
		return (0);
	current = cmd_list->head;
	while (current)
	{
		if (process_heredocs_in_single_cmd(current) == -1)
			return (-1);
		current = current->next;
	}
	return (0);
}

/* Processes all heredocs in a single command node */
int	process_heredocs_in_single_cmd(t_cmd_node *cmd_node)
{
	t_file_node	*file_current;

	if (!cmd_node || !cmd_node->file_list || !cmd_node->file_list->head)
		return (0);
	file_current = cmd_node->file_list->head;
	while (file_current)
	{
		if (file_current->redir_type == REDIR_HEREDOC)
		{
			if (create_heredoc(file_current->filename, cmd_node, file_current) == -1)
				return (-1);
		}
		file_current = file_current->next;
	}
	return (0);
}

/* Checks if cmd_list contains any heredocs */
int	cmd_list_has_heredocs(t_cmd_list *cmd_list)
{
	t_cmd_node	*cmd_current;
	t_file_node	*file_current;

	if (!cmd_list || !cmd_list->head)
		return (0);
	cmd_current = cmd_list->head;
	while (cmd_current)
	{
		if (cmd_current->file_list && cmd_current->file_list->head)
		{
			file_current = cmd_current->file_list->head;
			while (file_current)
			{
				if (file_current->redir_type == REDIR_HEREDOC)
					return (1);
				file_current = file_current->next;
			}
		}
		cmd_current = cmd_current->next;
	}
	return (0);
}

/* Main function to handle all heredocs in cmd_list before execution */
int	handle_cmd_list_heredocs(t_cmd_list *cmd_list)
{
	if (!cmd_list_has_heredocs(cmd_list))
		return (0);
	return (process_heredocs_in_cmd_list(cmd_list));
}
