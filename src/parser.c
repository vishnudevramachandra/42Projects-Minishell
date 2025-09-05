/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:03:37 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/05 13:14:49 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../include/parser.h"

/*	Adds to command list a new instantiated command node and returns it.
	Before returning also updates the list attrs */
static t_cmd_node	*add_cmd_node(
	t_cmd_node *cmd_node, t_cmd_list *cmds, t_lexer *lex)
{
	cmd_node->next = alloc_and_init_cmd_node(lex);
	cmds->tail = cmd_node->next;
	cmds->size++;
	return (cmd_node->next);
}

static t_token	*add_redir(
	t_token_type typ, t_cmd_node *cmd_node, t_token *tok, t_lexer *lex)
{
	t_file_list	*files;

	if (!cmd_node->file_list)
		cmd_node->file_list = alloc_and_init_file_list(lex);
	files = cmd_node->file_list;
	if (typ == WRITE)
		add_file_to_filelist(files, tok->data, REDIR_OUT, lex);
	else if (typ == APPEND)
		add_file_to_filelist(files, tok->data, REDIR_APPEND, lex);
	else if (typ == READ)
		add_file_to_filelist(files, tok->data, REDIR_IN, lex);
	else if (typ == HEREDOC)
		add_file_to_filelist(files, tok->data, REDIR_HEREDOC, lex);
	else
	{
		add_file_to_filelist(files, tok->data, REDIR_OUT, lex);
		add_file_to_filelist(files, tok->data, REDIR_IN, lex);
	}
	return (tok->next);
}

int	parse(t_cmd_list *cmds, t_lexer *lex)
{
	t_token			*tok;
	t_cmd_node		*cmd_node;
	
	cmds = gc_malloc(sizeof(t_env_list));
	if (!cmds)
		free_and_exit(lex);
	init_cmds(cmds, lex);
	tok = lex->toks;
	// while (tok)
	// {
	// 	printf("%s[%c], ", tok->data, tok->type);
	// 	tok = tok->next;
	// }
	// printf("\n");
	// return (1);
	while (tok && tok->type == CHAR_NULL)
		tok = tok->next;
	if (!tok)
		return (1);
	init_cmds(cmds, lex);
	cmd_node = cmds->head;
	while (!tok)
	{
		if (tok->type == CHAR_NULL)
			tok = tok->next;
		if (tok->type == PIPE)
		{
			cmd_node = add_cmd_node(cmd_node, cmds, lex);
			tok = tok->next;
		}
		else if (tok->type == WRITE || tok->type == READ || tok->type == APPEND
			|| tok->type == RW || tok->type == HEREDOC)
			tok = add_redir(tok->type, cmd_node, tok->next, lex);
		if (tok->type == WORD)
		{
			cmd_node->cmd = update_cmd(cmd_node->cmd, tok->data, lex);
			tok = tok->next;
		}
	}
	return (1);
}
