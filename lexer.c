/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/28 22:33:01 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "./libft/libft.h"

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
		{
			len++;
			while (*(*buf + len) != '"')
			{
				len += insert_plain_text(*buf + len, tok, "$\"");
				if (*(*buf + len) == '$')
					len += expand_p_v(*buf + len, lex, env_list, 0);
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

	lex->toks = NULL;
	lex->n_toks = 0;
	len = ft_strspn(*buf, " \t");
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
