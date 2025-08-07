/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:05:06 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/06 16:32:10 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	struct s_token	*list_toks;
	size_t			n_toks;
}	t_lexer;

enum e_token_type
{
	WORD = -1,
	PIPE = '|',
	WRITE = '>',
	READ = '<',
	APPEND = 'a',
	HEREDOC = 'h',
	RW = 'e',
	CHAR_NULL = 0,
};

int	lexer_build(char *linebuffer, t_lexer *lex);

#endif