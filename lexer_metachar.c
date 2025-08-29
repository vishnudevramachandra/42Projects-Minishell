/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_metachar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 09:51:11 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/29 14:10:21 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "lexer.h"
#include "./libft/libft.h"

int	is_next_tok_valid(char *non_valid_chars, char *buf, size_t len)
{
	if (ft_strchr(non_valid_chars, *(buf + len + ft_strspn(buf + len, " \t"))))
	{
		if (ft_strchr("\n", *(buf + len + ft_strspn(buf + len, " \t"))))
			printf("msh: syntax error near unexpected token `newline'\n");
		else
			printf("msh: syntax error near unexpected token `%c'\n",
				*(buf + len + ft_strspn(buf + len, " \t")));
		return (0);
	}
	return (1);
}

size_t	lb_pipe(char *buf, size_t len, t_token *tok, t_lexer *lex)
{
	if (tok == lex->toks
		|| '|' == *(buf + len + 1 + ft_strspn(buf + len + 1, " \t")))
	{
		printf("msh: syntax error near unexpected token `|'\n");
		return (clear_lexer(lex), len + ft_strlen(buf + len));
	}
	ft_strlcpy(tok->data, buf + len, 2);
	tok->type = *(buf + len);
	return (len + 1);
}

size_t	lb_redirects(char *buf, size_t len, t_token *tok, t_lexer *lex)
{
	size_t	i;

	if (ft_strnstr(buf + len, "<<", 2)
		|| ft_strnstr(buf + len, ">>", 2)
		|| ft_strnstr(buf + len, "<>", 2))
		i = 2;
	else
		i = 1;
	if (!is_next_tok_valid("|<>\n", buf, len + i))
		return (clear_lexer(lex), len + ft_strlen(buf + len));
	ft_strlcpy(tok->data, buf + len, i + 1);
	if (i < 1)
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
	(void)env_list;
	tok->data = malloc(3 * sizeof(char));
	if (!tok->data)
		cleanup_print_error_and_exit(lex);
	if (ft_strnstr(*buf + len, "|", 1))
		return (lb_pipe(*buf, len, tok, lex));
	else
		return (lb_redirects(*buf, len, tok, lex));
}
