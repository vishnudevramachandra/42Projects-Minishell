/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:03:37 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/05 15:56:12 by vramacha         ###   ########.fr       */
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

/* Adds the redirection */
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

int	is_inbuilt(char *word)
{
	if (!ft_strcmp("echo", word)
		|| !ft_strcmp("cd", word)
		|| !ft_strcmp("pwd", word)
		|| !ft_strcmp("export", word)
		|| !ft_strcmp("unset", word)
		|| !ft_strcmp("env", word)
		|| !ft_strcmp("exit", word))
		return (1);
	return (0);
}

void	parse_tokens(
	t_cmd_node *cmd_node, t_cmd_list *cmds, t_token *tok, t_lexer *lex)
{
	while (tok)
	{
		if (tok->type == CHAR_NULL)
			tok = tok->next;
		else if (tok->type == PIPE)
		{
			cmd_node = add_cmd_node(cmd_node, cmds, lex);
			tok = tok->next;
		}
		else if (tok->type == WRITE || tok->type == READ || tok->type == APPEND
			|| tok->type == RW || tok->type == HEREDOC)
			tok = add_redir(tok->type, cmd_node, tok->next, lex);
		else
		{
			if (!cmd_node->cmd)
				if (is_inbuilt(tok->data))
					cmd_node->cmd_type = 1;
			cmd_node->cmd = update_cmd(cmd_node->cmd, tok->data, lex);
			tok = tok->next;
		}
	}
}

int	parse(t_cmd_list **cmds, t_lexer *lex)
{
	t_token			*tok;

	*cmds = init_cmds(NULL, lex);
	tok = lex->toks;
	while (tok && tok->type == CHAR_NULL)
		tok = tok->next;
	if (!tok)
		return (1);
	init_cmds(*cmds, lex);
	parse_tokens((*cmds)->head, *cmds, tok, lex);
	return (1);
}
