/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:51:59 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/05 23:00:47 by vishnudevra      ###   ########.fr       */
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

void	add_word_to_tok(const char *linebuffer, size_t len, t_token *tok)
{
	size_t	prev_len;
	char	*ptr;

	if (!tok->data)
	{
		tok->data = malloc((len + 1) * sizeof(char));
		ft_strlcpy(tok->data, linebuffer, len + 1);
	}
	else
	{
		prev_len = ft_strlen(tok->data);
		ptr = malloc((prev_len + len + 1) * sizeof(char));
		ft_strlcpy(ptr, tok->data, prev_len + 1);
		ft_strlcpy(ptr + prev_len, linebuffer, len + 1);
		free(tok->data);
		tok->data = ptr;
	}
	tok->type = WORD;
}

size_t	insert_plain_text(
			const char *linebuffer, t_token *tok, char *end_of_word)
{
	size_t	len;

	len = ft_strcspn(linebuffer, end_of_word);
	add_word_to_tok(linebuffer, len, tok);
	return (len);
}

/* In place of leading tilde the value of $HOME (if non-null) is inserted */
size_t	expand_tilde(t_token *tok, const char *home)
{
	size_t	len;

	if (home)
	{
		len = ft_strlen(home);
		tok->data = malloc((len + 1) * sizeof(char));
		ft_strlcpy(tok->data, home, len + 1);
		tok->type = WORD;
	}
	return (1);
}

void	set_status(t_mini *mini, int nbr)
{
	mini->status = nbr;
}
