/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 19:03:37 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/28 22:58:03 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
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

void	add_file_to_filelist(t_file_list *files, char *name, t_redir_type typ)
{
	t_file_node	*file;
	t_file_node	*node;

	file = malloc(sizeof(t_file_node));
	if (!file)
		exit (1);
	file->filename = name;
	file->redir_type = typ;
	file->next = NULL;
	if (files->size < 1)
		files->head = file;
	else
	{
		node = files->head;
		while (node->next)
			node = node->next;
		node->next = file;
	}
	files->tail = file;
	files->size++;
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

/* appends the command - array of strings with the given token word */
void	update_cmd(char ***strs_addr, char *word)
{
	char	**strs;
	size_t	len;
	size_t	i;

	if (!*strs_addr)
	{
		strs = malloc(2 * sizeof(char *));
		if (!strs)
			exit (1);
		strs[0] = word;
		strs[1] = 0;
		strs_addr[0] = strs;
	}
	else
	{
		len = 0;
		while (strs_addr[0][len])
			len++;
		strs = malloc((len + 2) * sizeof(char *));
		if (!strs)
			exit (1);
		i = 0;
		while (i < len)
		{
			strs[i] = strs_addr[0][i];
			i++;
		}
		strs[i] = word;
		strs[i + 1] = 0;
		free(strs_addr[0]);
		strs_addr[0] = strs;
	}
}

int	parse(t_cmd_list *cmds, t_lexer *lex)
{
	t_token			*tok;
	t_cmd_node		*cmd_node;
	t_token_type	typ;

	tok = lex->toks;
	cmds->head = NULL;
	cmds->tail = NULL;
	cmds->size = 0;
	while (tok)
	{
		printf("%s[%c], ", tok->data, tok->type);
		tok = tok->next;
	}
	printf("\n");
	return (1);
	if (tok->type == CHAR_NULL)
		return (1);
	//TODO: what is cmds->prev_fd ?
	while (tok->type != CHAR_NULL)
	{
		if (tok->type == PIPE)
		{
			if (cmds->size < 1 || !next_word(tok->next))
			{
				printf("Syntax error\n");
				//TODO: housekeeping
			}
			cmd_node->next = alloc_and_init_cmd_node();
			cmd_node = cmd_node->next;
			cmds->tail = cmd_node;
			cmds->size++;
			tok = tok->next;
			if (tok->type == NEW_LINE)
				tok = tok->next;
		}
		if (tok->type == NEW_LINE)
		{
			if (tok->type == NEW_LINE)
				tok = tok->next;
			if (tok->type != CHAR_NULL)
			{
				if (cmds->size < 1)
				{
					cmd_node = alloc_and_init_cmd_node();
					cmds->head = cmd_node;
				}
				else
				{
					cmd_node->next = alloc_and_init_cmd_node();
					cmd_node = cmd_node->next;
				}
				cmds->tail = cmd_node;
				cmds->size++;
			}
		}
		if (tok->type == WRITE || tok->type == READ || tok->type == APPEND
			|| tok->type == RW || tok->type == HEREDOC)
		{
			if (cmds->size < 1)
			{
				cmd_node = alloc_and_init_cmd_node();
				cmds->head = cmd_node;
				cmds->tail = cmd_node;
				cmds->size++;
			}
			if (!cmd_node->file)
				cmd_node->file = alloc_and_init_file_list();
			typ = tok->type;
			tok = tok->next;
			if (tok->type != WORD)
			{
				printf("Syntax error\n");
				//TODO: housekeeping
			}
			if (typ == WRITE)
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_OUT);
			else if (typ == READ)
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_IN);
			else if (typ == APPEND)
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_APPEND);
			else if (typ == RW)
			{
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_IN);
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_OUT);
			}
			else
				add_file_to_filelist(cmd_node->file, tok->data, REDIR_HEREDOC);
			tok = tok->next;
		}
		if (tok->type == WORD)
		{
			if (cmds->size < 1)
			{
				cmd_node = alloc_and_init_cmd_node();
				cmds->head = cmd_node;
				cmds->tail = cmd_node;
				cmds->size++;
			}
			update_cmd(&cmd_node->cmd, tok->data);
			tok = tok->next;
		}
	}
	return (1);
}
