/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 17:56:59 by swied             #+#    #+#             */
/*   Updated: 2025/09/01 00:14:51 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* NOTHING DONE YET WITH HEREDOC | TOTAL MESS */

/* creates a new hd_line */
t_hd_line	*create_hd_line(char *content)
{
	t_hd_line	*new;

	new = gc_malloc(sizeof(t_hd_line));
	if (!new)
		return (NULL);
	new->line = content;
	new->next = NULL;
	return (new);
}

/* adds a line to the heredoc */
void	add_line_to_heredoc(t_hd_node *hd_node, char *line)
{
	t_hd_line	*new_line;
	t_hd_line	*current;

	new_line = create_hd_line(line);
	if (!new_line)
		return ;
	if (!hd_node->lines)
	{
		hd_node->lines = new_line;
		return ;
	}
	current = hd_node->lines;
	while (current->next)
		current = current->next;
	current->next = new_line;
}

/* checks if a line is equal to the delimiter */
int	is_delimiter(char *line, char *delimiter)
{
	int	len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	return (0);
}

/* creates a pipe and writes from hd_node into pipe */
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

/* writes from hd_node into pipe */
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
			write(write_fd, "\n", 1);
		}
		current = current->next;
	}
	return (0);
}
