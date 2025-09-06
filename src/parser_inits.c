/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_inits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 21:26:11 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/06 10:44:31 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

void	free_and_exit(t_lexer *lex)
{
	clx(lex);
	free_all_garbage();
	exit(1);
}

t_cmd_node	*alloc_and_init_cmd_node(t_lexer *lex)
{
	t_cmd_node	*cmd_node;

	cmd_node = gc_malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		free_and_exit(lex);
	cmd_node->cmd_type = 0;
	cmd_node->cmd = NULL;
	cmd_node->file_list = NULL;
	cmd_node->next = NULL;
	cmd_node->hd_list = NULL;
	return (cmd_node);
}

t_file_list	*alloc_and_init_file_list(t_lexer *lex)
{
	t_file_list	*files;

	files = gc_malloc(sizeof(t_file_list));
	if (!files)
		free_and_exit(lex);
	files->head = NULL;
	files->tail = NULL;
	files->size = 0;
	files->fd_infile = -1;
	files->fd_outfile = -1;
	return (files);
}

t_cmd_list	*init_cmds(t_cmd_list *cmds, t_lexer *lex)
{
	if (!cmds)
	{
		cmds = gc_malloc(sizeof(t_env_list));
		if (!cmds)
			free_and_exit(lex);
		cmds->head = NULL;
		cmds->tail = NULL;
		cmds->size = 0;
		cmds->prev_fd = -1;
	}
	else
	{
		cmds->head = alloc_and_init_cmd_node(lex);
		cmds->tail = cmds->head;
		cmds->size = 1;
	}
	return (cmds);
}
