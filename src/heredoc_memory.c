/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_memory.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 17:18:00 by swied             #+#    #+#             */
/*   Updated: 2025/09/10 17:18:38 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Create a new heredoc line node */
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

/* Add a line to heredoc node's lines list */
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

/* Initialize a new heredoc node */
t_hd_node	*init_heredoc_node(char *delimiter)
{
	t_hd_node	*node;

	node = gc_malloc(sizeof(t_hd_node));
	if (!node)
		return (NULL);
	node->lines = NULL;
	node->lim = ft_strdup(delimiter);
	if (!node->lim)
		return (NULL);
	add_to_gc(node->lim);
	node->file_node = NULL;
	node->next = NULL;
	return (node);
}

/* Add heredoc node to command's heredoc list */
void	add_heredoc_to_list(t_cmd_node *cmd_node, t_hd_node *hd_node)
{
	if (!cmd_node->hd_list->head)
	{
		cmd_node->hd_list->head = hd_node;
		cmd_node->hd_list->tail = hd_node;
		cmd_node->hd_list->size = 1;
	}
	else
	{
		cmd_node->hd_list->tail->next = hd_node;
		cmd_node->hd_list->tail = hd_node;
		cmd_node->hd_list->size++;
	}
}

/* Initialize heredoc list for a command node */
void	init_hd_list(t_cmd_node *cmd_node)
{
	cmd_node->hd_list = gc_malloc(sizeof(t_hd_list));
	if (!cmd_node->hd_list)
		return ;
	cmd_node->hd_list->head = NULL;
	cmd_node->hd_list->tail = NULL;
	cmd_node->hd_list->size = 0;
}
