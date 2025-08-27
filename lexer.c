/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/27 16:43:55 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "./libft/libft.h"

size_t	lb_on_metachar(
	char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	(void)env_list;
	tok->data = malloc(3 * sizeof(char));
	if (ft_strnstr(*buf + len, "<<", 2)
		|| ft_strnstr(*buf + len, ">>", 2)
		|| ft_strnstr(*buf + len, "<>", 2))
	{
		ft_strlcpy(tok->data, *buf + len, 3);
		if (ft_strnstr(*buf + len, "<<", 2))
			tok->type = HEREDOC;
		else if (ft_strnstr(*buf + len, ">>", 2))
			tok->type = APPEND;
		else
			tok->type = RW;
		return (len + 2);
	}
	else
	{
		ft_strlcpy(tok->data, *buf + len, 2);
		tok->type = *(*buf + len);
		return (len + 1);
	}
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
			len += expand_p_v(*buf + len, &tok, env_list, 1);
		if (*(*buf + len) == '"')
		{
			len++;
			while (*(*buf + len) != '"')
			{
				len += insert_plain_text(*buf + len, tok, "$\"");
				if (*(*buf + len) == '$')
					len += expand_p_v(*buf + len, &tok, env_list, 0);
			}
			len++;
		}
		if (*(*buf + len) == '\'')
		{
			len++;
			len += 1 + insert_plain_text(*buf + len, tok, "'");
		}
	}
	return (len);
}

size_t	lexer_build(char **buf, t_lexer *lex, t_env_list *env_list)
{
	size_t	len;
	t_token	*tok;

	lex->n_toks = 0;
	incr_lex(lex);
	len = ft_strspn(*buf, " \t");
	while (*(*buf + len))
	{
		if (ft_strchr("|<>\n", *(*buf + len)))
			len = lb_on_metachar(buf, len, env_list, lex);
		else
			len = lb_on_normchar(buf, len, env_list, lex);
		tok = get_last_token(lex);
		if (tok->type != CHAR_NULL)
			incr_lex(lex);
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
