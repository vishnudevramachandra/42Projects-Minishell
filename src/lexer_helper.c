/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:51:59 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/23 15:28:22 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft/libft.h"
#include "../include/lexer.h"

char	*buf_cat(char *old_buf, char *delim, char *str)
{
	char	*buf;

	if (delim)
	{
		buf = ft_strjoin(old_buf, delim);
		free(old_buf);
		if (!buf)
		{
			free(str);
			return (NULL);
		}
		old_buf = buf;
	}
	buf = ft_strjoin(old_buf, str);
	free(old_buf);
	free(str);
	return (buf);
}

t_token	*add_word_to_tok(const char *linebuffer, size_t len, t_lexer *lex)
{
	t_token	*tok;
	size_t	prev_len;
	char	*ptr;

	tok = get_last_token(lex);
	if (!tok->data)
	{
		tok->data = malloc((len + 1) * sizeof(char));
		if (!tok->data)
			return (NULL);
		ft_strlcpy(tok->data, linebuffer, len + 1);
	}
	else
	{
		prev_len = ft_strlen(tok->data);
		ptr = malloc((prev_len + len + 1) * sizeof(char));
		if (!ptr)
			return (NULL);
		ft_strlcpy(ptr, tok->data, prev_len + 1);
		ft_strlcpy(ptr + prev_len, linebuffer, len + 1);
		free(tok->data);
		tok->data = ptr;
	}
	tok->type = WORD;
	return (tok);
}

size_t	insert_plain_text(const char *linebuffer,
			t_lexer *lex, char *end_of_word, int exit_flag)
{
	size_t	len;
	t_token	*tok;

	len = ft_strcspn(linebuffer, end_of_word);
	tok = add_word_to_tok(linebuffer, len, lex);
	if (!tok)
	{
		if (exit_flag)
			cleanup_print_error_and_exit(lex);
		return (-1);
	}
	return (len);
}

/* In place of leading tilde the value of $HOME (if non-null) is inserted */
size_t	expand_tilde(t_token *tok, const char *home, t_lexer *lex)
{
	size_t	len;

	if (home)
	{
		len = ft_strlen(home);
		tok->data = malloc((len + 1) * sizeof(char));
		if (!tok->data)
			cleanup_print_error_and_exit(lex);
		ft_strlcpy(tok->data, home, len + 1);
		tok->type = WORD;
	}
	return (1);
}

void	set_status(t_mini *mini, int nbr)
{
	mini->status = nbr;
}
