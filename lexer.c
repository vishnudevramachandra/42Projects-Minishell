/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/02 15:38:57 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"
#include "./libft/libft.h"

void	lb_mline(char **buf, size_t len, t_lexer *lex, char c)
{
	char	*old_buf;
	char	*str;

	old_buf = *buf;
	*buf = ft_strjoin(old_buf, "\n");
	free(old_buf);
	str = readline("<");
	if (!str || *str == '\n')
	{
		if (!str)
			printf("msh: unexpected EOF while looking for matching `%c'\n", c);
		add_history(*buf);
		clear_lexer(lex);
		(*buf)[len] = 0;
		return ;
	}
	old_buf = *buf;
	*buf = ft_strjoin(old_buf, str);
	free (old_buf);
	free (str);
}

size_t	lb_on_dquote(char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	++len;
	while (*(*buf + len) != '"')
	{
		len += insert_plain_text(*buf + len, tok, "$\"");
		if (*(*buf + len) == '$')
			len += expand_p_v(*buf + len, lex, env_list, 0);
		while (!strchr(*buf + len, '"'))
		{
			lb_mline(buf, len, lex, '"');
			if (!*(*buf + len))
				return (len); //TODO: set $? to have a value of 1
		}
	}
	return (++len);
}

size_t	lb_on_squote(char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;

	(void)env_list;
	tok = get_last_token(lex);
	++len;
	while (!strchr(*buf + len, '\''))
	{
		lb_mline(buf, len, lex, '\'');
		if (!*(*buf + len))
			return (len); //TODO: set $? to have a value of 1
	}
	len += 1 + insert_plain_text(*buf + len, tok, "'");
	return (len);
}

size_t	lb_on_normchar(
	char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	while (!ft_strchr(" \t\n|<>", *(*buf + len)))
	{
		if (*(*buf + len) == '~'
			&& ft_strchr(" \t\n|<>/", *(*buf + len + 1))
			&& tok->type == CHAR_NULL)
			len += expand_tilde(tok, get_env_value(env_list, "HOME"));
		if (ft_strcspn(*buf + len, " \t\n|<>$\"'"))
			len += insert_plain_text(*buf + len, tok, " \t\n|<>$\"'");
		if (*(*buf + len) == '$')
		{
			len += expand_p_v(*buf + len, lex, env_list, 1);
			tok = get_last_token(lex);
		}
		if (*(*buf + len) == '"')
			len = lb_on_dquote(buf, len, env_list, lex);
		if (*(*buf + len) == '\'')
			len = lb_on_squote(buf, len, env_list, lex);
	}
	return (len);
}

size_t	lexer_build(char **buf, t_lexer *lex, t_env_list *env_list)
{
	size_t	len;

	lex->toks = NULL;
	lex->n_toks = 0;
	len = ft_strspn(*buf, " \t\n");
	while (*(*buf + len))
	{
		incr_lex(lex);
		if (ft_strchr("|<>\n", *(*buf + len)))
			len = lb_on_metachar(buf, len, env_list, lex);
		else
			len = lb_on_normchar(buf, len, env_list, lex);
		len += ft_strspn(*buf + len, " \t");
	}
	return (lex->n_toks);
}

// int	main(void)
// {
// 	char		str[] = "<text.txt cat ~/yo' bl<|'mama >\"ab$HOME*\"$var et" ;
// 	t_lexer		lex;
// 	t_env_list	env_list;
// 	t_env_node	*node;

// 	node = malloc(sizeof(t_env_node));
// 	node->variable = "HOME";
// 	node->value = "/Users/root";
// 	node->is_export = 0;
// 	env_list.head = node;
// 	node->next = malloc(sizeof(t_env_node));
// 	node = node->next;
// 	node->variable = "var";
// 	node->value = "\ta:bs>mm c\t";
// 	node->is_export = 0;	
// 	node->next = malloc(sizeof(t_env_node));	
// 	node = node->next;
// 	node->variable = "IFS";
// 	node->value = " \t\n:";
// 	node->is_export = 0;
// 	node->next = NULL;
// 	lexer_build(str, &lex, &env_list);
// }
