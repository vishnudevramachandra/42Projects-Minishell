/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:03:37 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/12 08:39:32 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "parser.h"

t_cmd_node	*alloc_and_init_cmd_node(void)
{
	t_cmd_node	*cmd_node;

	cmd_node = malloc(sizeof(t_cmd_node));
	if (!cmd_node)
		exit (1);
	cmd_node->cmd = NULL;
	cmd_node->file = NULL;
	cmd_node->next = NULL;
	cmd_node->hd_list = NULL;
	return (cmd_node);
}

t_file_list	*alloc_and_init_file_list(void)
{
	t_file_list	*files;

	files = malloc(sizeof(t_file_list));
	if (!files)
		exit (1);
	files->head = NULL;
	files->tail = NULL;
	files->size = 0;
	files->fd_infile = 0;
	files->fd_outfile = 1;	
	return (files);
}
	
/* returns next word if it exists before running into pipe or tokens' end */
t_token	*next_word(t_token *tok)
{
	while (tok)
	{
		if (tok->type == PIPE)
			return (NULL);
		if (tok->type == WORD)
			return (tok);
		tok = tok->next;
	}
	return (NULL);
}

int	parse(t_cmd_list *cmds, t_lexer *lex)
{
	t_token		*tok;
	t_cmd_node	*cmd_node;

	tok = lex->toks;
	if (!tok->data)
	{
		cmds = NULL;
		return (1);
	}
	cmd_node = alloc_and_init_cmd_node();
	cmds->head = cmd_node;
	cmds->tail = cmd_node;
	cmds->size = 1;
	//TODO: what is cmds->prev_fd ?
	while (tok->data)
	{
		if (tok->type == PIPE)
		{
			if (!cmd_node->cmd && !next_word(tok->next))
			{
				printf("Syntax error\n");
				//TODO: housekeeping
			}
			cmd_node->next = alloc_and_init_cmd_node();
			cmd_node = cmd_node->next;
			cmds->tail = cmd_node;
			cmds->size++;
			tok = tok->next;
		}
		if ((tok->type == WRITE || tok->type == READ || tok->type == APPEND
			|| tok->type == RW || tok->type == HEREDOC) && !cmd_node->file)
			cmd_node->file = alloc_and_init_file_list();
		if (tok->type == WRITE)
		{
			if (tok->next->type != WORD)
			{
				printf("Syntax error\n");
				//TODO: housekeeping
			}
			
		}
		
	}
}