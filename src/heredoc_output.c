/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_output.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:17:00 by swied             #+#    #+#             */
/*   Updated: 2025/09/10 19:13:15 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Print EOF warning message */
static void	print_eof_warning(char *delimiter)
{
	write(STDERR_FILENO, "minishell: warning: here-document delimited by end-of-file (wanted `", 67);
	write(STDERR_FILENO, delimiter, ft_strlen(delimiter));
	write(STDERR_FILENO, "')\n", 3);
}

/* Collect heredoc input with proper signal handling */
int	collect_heredoc_input(char *delimiter, int write_fd)
{
	char	*line;

	setup_heredoc_signals();
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			print_eof_warning(delimiter);
			break ;
		}
		if (is_delimiter_match(line, delimiter))
		{
			free(line);
			break ;
		}
		write(write_fd, line, ft_strlen(line));
		write(write_fd, "\n", 1);
		free(line);
	}
	close(write_fd);
	exit(0);
}

/* Read heredoc content from pipe and store in lines */
int	read_heredoc_content(t_hd_node *hd_node, int read_fd)
{
	char	*line;
	char	*stored_line;

	while (1)
	{
		line = get_next_line(read_fd);
		if (!line)
			break ;
		stored_line = ft_strdup(line);
		if (!stored_line)
		{
			free(line);
			return (-1);
		}
		add_to_gc(stored_line);
		add_line_to_heredoc(hd_node, stored_line);
		free(line);
	}
	return (0);
}

/* Write heredoc content to pipe */
int	write_heredoc_to_pipe(t_hd_node *hd_node, int write_fd)
{
	t_hd_line	*current;

	if (!hd_node || !hd_node->lines)
		return (-1);
	current = hd_node->lines;
	while (current)
	{
		if (current->line)
		{
			write(write_fd, current->line, ft_strlen(current->line));
		}
		current = current->next;
	}
	return (0);
}

/* Create pipe and write heredoc content to it */
int	create_heredoc_fd(t_hd_node *hd_node)
{
	int	pipe_fd[2];

	if (!hd_node)
		return (-1);
	if (pipe(pipe_fd) == -1)
		return (-1);
	write_heredoc_to_pipe(hd_node, pipe_fd[1]);
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}
