/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:51:11 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/05 15:20:10 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../include/lexer.h"
#include "./libft/libft.h"

static void	prt_stx_err(char c, t_env_list *env_list)
{
	(void)env_list;
	//TODO: set $? to have a value of 258
	if (ft_strchr("\n", c))
		printf("msh: syntax error near unexpected token `newline'\n");
	else
		printf("msh: syntax error near unexpected token `%c'\n", c);
}

static size_t	lb_pipe(
	char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;
	char	*str;

	tok = get_last_token(lex);
	if (tok == lex->toks
		|| '|' == *(*buf + len + 1 + ft_strspn(*buf + len + 1, " \t\n")))
		return (prt_stx_err(*(*buf + len), env_list),
			clear_lexer(lex), ft_strlen(*buf));
	ft_strlcpy(tok->data, *buf + len, 2);
	tok->type = *(*buf + len);
	len += 1 + ft_strspn(*buf + len + 1, " \t\n");
	while (!*(*buf + len))
	{
		str = readline("<");
		if (!str) //TODO: set $? to have a value of 258
			return (printf("msh: syntax error: unexpected end of file\n"),
				clear_lexer(lex), ft_strlen(*buf));
		else if (*str == '\n') //TODO: set $? to have a value of 1
			return (free(str), clear_lexer(lex), ft_strlen(*buf));
		*buf = buf_cat(*buf, NULL, str);
		if (!*buf)
			cleanup_print_error_and_exit(lex);
		len += ft_strspn(*buf + len, " \t\n");
	}
	return (len);
}

static int	is_next_tok_valid(
	char *non_valid_chars, char *buf, size_t len, t_env_list *env_list)
{
	if (ft_strchr(non_valid_chars, *(buf + len + ft_strspn(buf + len, " \t"))))
	{
		prt_stx_err(*(buf + len + ft_strspn(buf + len, " \t")), env_list);
		return (0);
	}
	return (1);
}

static size_t	lb_redirects(
	char *buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	size_t	i;
	t_token	*tok;

	tok = get_last_token(lex);
	if (ft_strnstr(buf + len, "<<", 2)
		|| ft_strnstr(buf + len, ">>", 2)
		|| ft_strnstr(buf + len, "<>", 2))
		i = 2;
	else
		i = 1;
	if (!is_next_tok_valid("|<>\n", buf, len + i, env_list))
		return (clear_lexer(lex), ft_strlen(buf));
	ft_strlcpy(tok->data, buf + len, i + 1);
	if (i < 2)
		tok->type = *(buf + len);
	else
	{
		if (ft_strnstr(buf + len, "<<", 2))
			tok->type = HEREDOC;
		else if (ft_strnstr(buf + len, ">>", 2))
			tok->type = APPEND;
		else
			tok->type = RW;
	}
	return (len + i);
}

size_t	lb_on_metachar(
	char **buf, size_t len, t_env_list *env_list, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	tok->data = malloc(3 * sizeof(char));
	if (!tok->data)
		cleanup_print_error_and_exit(lex);
	if (ft_strnstr(*buf + len, "|", 1))
		return (lb_pipe(buf, len, env_list, lex));
	else
		return (lb_redirects(*buf, len, env_list, lex));
}
