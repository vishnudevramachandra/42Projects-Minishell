/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:05:06 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/13 15:12:43 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <stddef.h>
# include <stdbool.h>

typedef struct s_token
{
	char			*data;
	int				type;
	struct s_token	*next;
}	t_token;

typedef struct s_lexer
{
	struct s_token	*toks;
	size_t			n_toks;
}	t_lexer;

typedef enum e_token_type
{
	WORD = -1,
	PIPE = '|',
	WRITE = '>',
	READ = '<',
	APPEND = 'a',
	HEREDOC = 'h',
	RW = 'e',
	NEW_LINE = '\n',
	CHAR_NULL = 0,
}	t_token_type;

typedef struct s_env_list	t_env_list;
typedef struct s_env_node	t_env_node;

size_t	ft_strcspn(const char *s, const char *charset);
size_t	ft_strspn(const char *s, const char *charset);
void	init_token(t_token *tok);
size_t	insert_plain_text(const char *linebuffer, t_token *tok, char *end_of_word);
int		lexer_build(const char *linebuffer, t_lexer *lex, t_env_list *env_list);
size_t	expand_tilde(t_token *tok, const char *home);
size_t	expand_p_v(const char *linebuffer, t_token **tok, t_env_list *env_list,
			int sep_fields_into_words);

typedef struct s_env_node
{
	char				*variable;
	char				*value;
	bool				is_export;
	t_env_node			*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	t_env_node	*tail;
	size_t		size;
}	t_env_list;

char	*get_env_value(t_env_list *env_list, char *var);

#endif