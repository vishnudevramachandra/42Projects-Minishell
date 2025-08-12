/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/11 20:11:25 by vishnudevra      ###   ########.fr       */
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

int	lexer_build(const char *linebuffer, t_lexer *lex, t_env_list *env_list)
{
	size_t	len;
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (0);
	init_token(tok);
	lex->toks = tok;
	lex->n_toks = 1;
	linebuffer += ft_strspn(linebuffer, " \t");
	while (*linebuffer)
	{
		if (ft_strchr("|<>\n", *linebuffer))
		{
			tok->data = malloc(3 * sizeof(char));
			if (ft_strnstr(linebuffer, "<<", 2)
				|| ft_strnstr(linebuffer, ">>", 2)
				|| ft_strnstr(linebuffer, "<>", 2))
			{
				ft_strlcpy(tok->data, linebuffer, 3);
				if (ft_strnstr(linebuffer, "<<", 2))
					tok->type = HEREDOC;
				else if (ft_strnstr(linebuffer, ">>", 2))
					tok->type = APPEND;
				else
					tok->type = RW;
				linebuffer += 2;
			}
			else
			{
				ft_strlcpy(tok->data, linebuffer, 2);
				tok->type = *linebuffer;
				++linebuffer;
			}
		}
		else
		{
			len = 0;
			while (!ft_strchr(" \t\n|<>", *(linebuffer + len)))
			{
				if (len < 1 && *(linebuffer) == '~'
					&& ft_strchr(" \t\n|<>/", *(linebuffer + 1)))
					len = expand_tilde(
							linebuffer, tok, get_env_value(env_list, "HOME"));
				if (ft_strcspn(linebuffer + len, " \t\n|<>$\"'"))
					len += insert_plain_text(
								linebuffer + len, tok, " \t\n|<>$\"'");
				if (*(linebuffer + len) == '$')
					len += expand_p_v(linebuffer + len, &tok, env_list, 1);
				if (*(linebuffer + len) == '"')
				{
					len++;
					while (*(linebuffer + len) != '"')
					{
						len += insert_plain_text(
									linebuffer + len, tok, "$\"");
						if (*(linebuffer + len) == '$')
							len += expand_p_v(linebuffer + len, &tok, env_list, 0);
					}
					len++;
				}
				if (*(linebuffer + len) == '\'')
				{
					len++;
					len += 1 + insert_plain_text(linebuffer + len, tok, "'");
				}
			}
			linebuffer += len;
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
		linebuffer += ft_strspn(linebuffer, " \t");
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
