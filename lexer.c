/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:31:01 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/07 10:18:47 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lexer.h"
#include "libft.h"

static size_t	ft_strcspn(const char *s, const char *charset)
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

static size_t	ft_strspn(const char *s, const char *charset)
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

static void	init_token(t_token *tok)
{
	tok->data = NULL;
	tok->next = NULL;
	tok->type = CHAR_NULL;
}

int	lexer_build(char *linebuffer, t_lexer *lex)
{
	size_t	len;
	t_token	*tok;

	tok = malloc(sizeof(t_token));
	if (!tok)
		return (0);
	init_token(tok);
	lex->list_toks = tok;
	lex->n_toks = 1;
	linebuffer += ft_strspn(linebuffer, " \t\n");
	while (*linebuffer)
	{
		if (ft_strchr("|<>", *linebuffer))
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
				len = len + ft_strcspn(linebuffer + len, " \t\n|<>\"'");
				if (*(linebuffer + len) == '"')
					len = len + 1 + ft_strcspn(linebuffer + len + 1, "\"");
				if (*(linebuffer + len) == '\'')
					len = len + 1 + ft_strcspn(linebuffer + len + 1, "'");
			}
			tok->data = malloc((len + 1) * sizeof(char));
			ft_strlcpy(tok->data, linebuffer, len + 1);
			tok->type = WORD;
			linebuffer += len;
		}
		tok->next = malloc(sizeof(t_token));
		if (!tok->next)
			return (0);
		init_token(tok->next);
		tok = tok->next;
		++(lex->n_toks);
	}
	return (lex->n_toks);
}

int main(void)
{
	char	str[] = "<text.txt "
}