/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_allot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 01:14:48 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/05 15:12:32 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parser.h"

static t_file_node	*create_file_node(
	char *name, t_redir_type typ, t_lexer *lex)
{
	t_file_node	*file;

	file = gc_malloc(sizeof(t_file_node));
	if (!file)
		free_and_exit(lex);
	if (!name)
		file->filename = NULL;
	else
	{
		file->filename = gc_malloc(ft_strlen(name) + 1);
		if (!file->filename)
			free_and_exit(lex);
		ft_strlcpy(file->filename, name, ft_strlen(name) + 1);
	}
	file->redir_type = typ;
	file->next = NULL;
	return (file);
}

/* setup file node, allot filename and append it to file list */
void	add_file_to_filelist(
	t_file_list *files, char *name, t_redir_type typ, t_lexer *lex)
{
	t_file_node	*file;
	t_file_node	*node;

	file = create_file_node(name, typ, lex);
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

static char	*str_dup(char *src, size_t len, t_lexer *lex)
{
	char	*dst;

	dst = gc_malloc(len + 1);
	if (!dst)
		free_and_exit(lex);
	ft_strlcpy(dst, src, len + 1);
	return (dst);
}

/* appends the argument "word" to command array (of strings) */
char	**update_cmd(char **cmd, char *word, t_lexer *lex)
{
	char	**strs;
	size_t	len;
	size_t	i;

	len = 0;
	if (cmd)
		while (cmd[len])
			len++;
	strs = gc_malloc((len + 2) * sizeof(char *));
	if (!strs)
		free_and_exit(lex);
	i = 0;
	while (i < len)
	{
		strs[i] = str_dup(cmd[i], ft_strlen(cmd[i]), lex);
		i++;
	}
	strs[i] = str_dup(word, ft_strlen(word), lex);
	strs[i + 1] = 0;
	return (strs);
}
