/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:51:11 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/22 16:04:48 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include "../include/lexer.h"
#include "./libft/libft.h"

static void	prt_err(char *buf, size_t len)
{
	char	c;

	c = *(buf + len + ft_strspn(buf + len, " \t"));
	if (ft_strchr("\n", c))
		ft_putendl_fd("msh: syntax error near unexpected token `newline'", 2);
	else
	{
		ft_putstr_fd("msh: syntax error near unexpected token `", 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("'", 2);
	}
}

static size_t	lb_pipe(
	char **buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;
	char	*str;

	tok = get_last_token(lex);
	if (tok == lex->toks
		|| '|' == *(*buf + len + 1 + ft_strspn(*buf + len + 1, " \t\n")))
		return (prt_err(*buf, len + 1), set_status(mini, 258), clx(lex),
			ft_strlen(*buf));
	ft_strlcpy(tok->data, *buf + len, 2);
	tok->type = *(*buf + len);
	len += 1 + ft_strspn(*buf + len + 1, " \t\n");
	while (!*(*buf + len))
	{
		str = readline("<");
		if (!str)
			return (ft_putendl_fd("msh: syntax error: unexpected EOF", 2),
				set_status(mini, 258), clx(lex), ft_strlen(*buf));
		else if (*str == '\n')
			return (set_status(mini, 1), free(str), clx(lex), ft_strlen(*buf));
		*buf = buf_cat(*buf, NULL, str);
		if (!*buf)
			cleanup_print_error_and_exit(lex);
		len += ft_strspn(*buf + len, " \t\n");
	}
	return (len);
}

static int	is_next_tok_valid(
	char *non_valid_chars, char *buf, size_t len)
{
	if (ft_strchr(non_valid_chars, *(buf + len + ft_strspn(buf + len, " \t"))))
		return (0);
	return (1);
}

static size_t	lb_redirects(
	char *buf, size_t len, t_mini *mini, t_lexer *lex)
{
	size_t	i;
	t_token	*tok;

	tok = get_last_token(lex);
	if (ft_strnstr(buf + len, "<<", 2) || ft_strnstr(buf + len, ">>", 2)
		|| ft_strnstr(buf + len, "<>", 2))
		i = 2;
	else
		i = 1;
	if (!is_next_tok_valid("|<>\n", buf, len + i))
		return (prt_err(buf, len + i), set_status(mini, 258), clx(lex),
			ft_strlen(buf));
	ft_strlcpy(tok->data, buf + len, i + 1);
	if (i < 2)
		tok->type = *(buf + len);
	else
	{
		if (ft_strnstr(buf + len, "<<", 2))
			i += lb_heredoc(buf, len + i, mini, lex);
		else if (ft_strnstr(buf + len, ">>", 2))
			tok->type = APPEND;
		else
			tok->type = RW;
	}
	return (len + i);
}

size_t	lb_on_metachar(
	char **buf, size_t len, t_mini *mini, t_lexer *lex)
{
	t_token	*tok;

	tok = get_last_token(lex);
	tok->data = malloc(3 * sizeof(char));
	if (!tok->data)
		cleanup_print_error_and_exit(lex);
	if (ft_strnstr(*buf + len, "|", 1))
		return (lb_pipe(buf, len, mini, lex));
	else
		return (lb_redirects(*buf, len, mini, lex));
}
