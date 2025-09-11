/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:16:00 by swied             #+#    #+#             */
/*   Updated: 2025/09/11 12:39:03 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Check if line matches delimiter (from heredoc_io.c) */
int	is_delimiter_match(char *line, char *delimiter)
{
	int	line_len;
	int	delim_len;

	if (!line || !delimiter)
		return (0);
	line_len = ft_strlen(line);
	delim_len = ft_strlen(delimiter);
	if (line_len > 0 && line[line_len - 1] == '\n')
		line_len--;
	if (line_len != delim_len)
		return (0);
	return (ft_strncmp(line, delimiter, delim_len) == 0);
}

/* Check if line equals delimiter (from heredoc_utils.c) */
int	is_delimiter(char *line, char *delimiter)
{
	int	len;
	int	delim_len;

	if (!line || !delimiter)
		return (0);
	len = ft_strlen(line);
	delim_len = ft_strlen(delimiter);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	if (len != delim_len)
		return (0);
	return (ft_strncmp(line, delimiter, delim_len) == 0);
}

/* Check if cmd_list contains any heredocs */
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

/* Process all heredocs in a single command node */
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
