/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/06 10:44:31 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../include/lexer.h"
#include "./libft/libft.h"

static void	prt_err(char c)
{
	ft_putstr_fd("msh: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putendl_fd("'", 2);
}

static size_t	lb_on_dquote(
	char **buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;
	char	*str;

	tok = get_last_token(lex);
	++len;
	while (*(*buf + len) != '"')
	{
		while (!strchr(*buf + len, '"'))
		{
			str = readline("<");
			if (!str)
				return (prt_err('"'), set_status(mini, 258), clx(lex),
					ft_strlen(*buf));
			else if (*str == '\n')
				return (set_status(mini, 1), free(str), clx(lex),
					ft_strlen(*buf));
			*buf = buf_cat(*buf, "\n", str);
			if (!*buf)
				cleanup_print_error_and_exit(lex);
		}
		len += insert_plain_text(*buf + len, tok, "$\"");
		if (*(*buf + len) == '$')
			len += expand_p_v(*buf + len, lex, mini, 0);
	}
	return (++len);
}

static size_t	lb_on_squote(
	char **buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;
	char	*str;

	tok = get_last_token(lex);
	++len;
	while (!strchr(*buf + len, '\''))
	{
		str = readline("<");
		if (!str)
			return (prt_err('\''), set_status(mini, 258), clx(lex),
				ft_strlen(*buf));
		else if (*str == '\n')
			return (set_status(mini, 1), free(str), clx(lex),
				ft_strlen(*buf));
		*buf = buf_cat(*buf, "\n", str);
		if (!*buf)
			cleanup_print_error_and_exit(lex);
	}
	len += 1 + insert_plain_text(*buf + len, tok, "'");
	return (len);
}

static size_t	lb_on_normchar(
	char **buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	while (!ft_strchr(" \t\n|<>", *(*buf + len)))
	{
		if (*(*buf + len) == '~'
			&& ft_strchr(" \t\n|<>/", *(*buf + len + 1))
			&& tok->type == CHAR_NULL)
			len += expand_tilde(tok, get_env_value(mini->env_list, "HOME"));
		if (ft_strcspn(*buf + len, " \t\n|<>$\"'"))
			len += insert_plain_text(*buf + len, tok, " \t\n|<>$\"'");
		if (*(*buf + len) == '$')
		{
			len += expand_p_v(*buf + len, lex, mini, 1);
			tok = get_last_token(lex);
		}
		if (*(*buf + len) == '"')
			len = lb_on_dquote(buf, len, mini, lex);
		if (*(*buf + len) == '\'')
			len = lb_on_squote(buf, len, mini, lex);
	}
	return (len);
}

size_t	lexer_build(char **buf, t_lexer *lex, t_mini *mini)
{
	size_t	len;

	lex->toks = NULL;
	lex->n_toks = 0;
	if (**buf == '\n')
	{
		mini->status = 1;
		free(*buf);
		*buf = NULL;
		return (lex->n_toks);
	}
	len = ft_strspn(*buf, " \t");
	while (*(*buf + len))
	{
		incr_lex(lex);
		if (ft_strchr("|<>\n", *(*buf + len)))
			len = lb_on_metachar(buf, len, mini, lex);
		else
			len = lb_on_normchar(buf, len, mini, lex);
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
