/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/26 17:56:53 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "./libft/libft.h"

size_t	ft_strcspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr(charset, s[i]))
			break ;
		i++;
	}
	return (i);
}

size_t	ft_strspn(const char *s, const char *charset)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (!ft_strchr(charset, s[i]))
			break ;
		i++;
	}
	return (i);
}

int	lexer_build(char **linebuffer, t_lexer *lex, t_env_list *env_list)
{
	size_t	len;
	t_token	*tok;
	char	*buf;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (0);
	init_token(tok);
	lex->toks = tok;
	lex->n_toks = 1;
	buf = *linebuffer;
	buf += ft_strspn(buf, " \t");
	while (*buf)
	{
		if (ft_strchr("|<>\n", *buf))
		{
			tok->data = malloc(3 * sizeof(char));
			if (ft_strnstr(buf, "<<", 2)
				|| ft_strnstr(buf, ">>", 2)
				|| ft_strnstr(buf, "<>", 2))
			{
				ft_strlcpy(tok->data, buf, 3);
				if (ft_strnstr(buf, "<<", 2))
					tok->type = HEREDOC;
				else if (ft_strnstr(buf, ">>", 2))
					tok->type = APPEND;
				else
					tok->type = RW;
				buf += 2;
			}
			else
			{
				ft_strlcpy(tok->data, buf, 2);
				tok->type = *buf;
				++buf;
			}
		}
		else
		{
			len = 0;
			while (!ft_strchr(" \t\n|<>", *(buf + len)))
			{
				if (len < 1 && *(buf) == '~'
					&& ft_strchr(" \t\n|<>/", *(buf + 1)))
					len = expand_tilde(tok, get_env_value(env_list, "HOME"));
				if (ft_strcspn(buf + len, " \t\n|<>$\"'"))
					len += insert_plain_text(
								buf + len, tok, " \t\n|<>$\"'");
				if (*(buf + len) == '$')
					len += expand_p_v(buf + len, &tok, env_list, 1);
				if (*(buf + len) == '"')
				{
					len++;
					while (*(buf + len) != '"')
					{
						len += insert_plain_text(
									buf + len, tok, "$\"");
						if (*(buf + len) == '$')
							len += expand_p_v(buf + len, &tok, env_list, 0);
					}
					len++;
				}
				if (*(buf + len) == '\'')
				{
					len++;
					len += 1 + insert_plain_text(buf + len, tok, "'");
				}
			}
			buf += len;
		}
		if (tok->data)
		{
			tok->next = malloc(sizeof(t_token));
			if (!tok->next)
				return (0);
			init_token(tok->next);
			tok = tok->next;
			++(lex->n_toks);
		}
		buf += ft_strspn(buf, " \t");
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
