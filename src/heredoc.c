/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 01:39:48 by swied             #+#    #+#             */
/*   Updated: 2025/07/29 02:34:10 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

t_hd_node	*create_hd_node(char *lim)
{
	t_hd_node	*new;

	new = malloc(sizeof(t_hd_node));
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
	//do_heredoc();
	return (0);
}
