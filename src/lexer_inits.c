/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_inits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 15:44:39 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/06 10:44:31 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../include/lexer.h"

/* initialize token to default 'null' type */
static void	init_token(t_token *tok)
{
	tok->data = NULL;
	tok->next = NULL;
	tok->type = CHAR_NULL;
}

void	clx(t_lexer *lex)
{
	t_token	*tok;
	t_token	*ptr;

	tok = lex->toks;
	while (tok)
	{
		ptr = tok;
		tok = tok->next;
		if (ptr->data)
			free(ptr->data);
		free(ptr);
	}
	lex->toks = NULL;
	lex->n_toks = 0;
}

void	cleanup_print_error_and_exit(t_lexer *lex)
{
	clx(lex);
	perror("Malloc error: ");
	exit (1);
}

t_token	*get_last_token(t_lexer *lex)
{
	t_token	*tok;

	tok = lex->toks;
	while (tok->next)
		tok = tok->next;
	return (tok);
}

/* add an initialized token to the end of token list in lexer */
int	incr_lex(t_lexer *lex)
{
	t_token	*tok;

	if (lex->n_toks < 1)
	{
		lex->toks = malloc(sizeof(t_token));
		if (!lex->toks)
			cleanup_print_error_and_exit(NULL);
		tok = lex->toks;
	}
	else
	{
		tok = get_last_token(lex);
		tok->next = malloc(sizeof(t_token));
		if (!tok->next)
			cleanup_print_error_and_exit(lex);
		tok = tok->next;
	}
	init_token(tok);
	++(lex->n_toks);
	return (1);
}
