/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vishnudevramachandra <vishnudevramachan    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:23:43 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/28 00:16:44 by vishnudevra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft/libft.h"
#include "lexer.h"

static size_t	extract_val_of_var(
	char **val, const char *linebuffer, t_env_list *env_list)
{
	size_t	len;
	char	*name;

	len = ft_strspn(linebuffer,
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	name = malloc((len + 1) * sizeof(char));
	ft_strlcpy(name, linebuffer, len + 1);
	*val = get_env_value(env_list, name);
	free(name);
	return (len);
}

static void	extract_sps_sep_from_ifs(
	char **sps, char **sep, t_env_list *env_list, t_lexer *lex)
{
	*sps = set_inter(" \t\n", get_env_value(env_list, "IFS"));
	if (!*sps)
		cleanup_print_error_and_exit(lex->toks);
	*sep = set_diff(get_env_value(env_list, "IFS"), *sps);
	if (!*sep)
	{
		free(*sps);
		cleanup_print_error_and_exit(lex->toks);
	}
}

/* add fields (defined using IFS contents) as tokens */
static void	fields_to_words(
	const char *val, t_env_list *env_list, t_lexer *lex)
{
	char	*sps;
	char	*sep;
	t_token	*tok;

	extract_sps_sep_from_ifs(&sps, &sep, env_list, lex);
	if (ft_strspn(val, sps))
	{
		if (get_last_token(lex)->type != CHAR_NULL)
			incr_lex(lex);
		val += ft_strspn(val, sps);
	}
	while (*val)
	{
		tok = get_last_token(lex);
		if (ft_strcspn(val, sep) < ft_strcspn(val, sps))
			val += 1 + insert_plain_text(val, tok, sep);
		else
		{
			val += insert_plain_text(val, tok, sps);
			if (!*val)
				break ;
		}
		incr_lex(lex);
		val += ft_strspn(val, sps);
	}
}

/* Expand parameter/variable and when not enclosed within double quotes turn the
   fields into words */
size_t	expand_p_v(const char *linebuffer, t_lexer *lex, t_env_list *env_list,
			int sep_fields_into_words)
{
	size_t	len;
	char	*val;
	t_token	*tok;

	tok = get_last_token(lex);
	if (*(linebuffer + 1) == '?')
	{
		//TODO: exit status of most recent foreground execution
		return (2);
	}
	else if (*(linebuffer + 1) == '$')
		return (add_word_to_tok(linebuffer, 2, tok), 2);
	else if (ft_isalnum(*(linebuffer + 1)))
	{
		len = 1 + extract_val_of_var(&val, linebuffer + 1, env_list);
		if (val)
		{
			if (sep_fields_into_words)
				fields_to_words(val, env_list, lex);
			else
				add_word_to_tok(val, ft_strlen(val), tok);
		}
		return (len);
	}
	len = 1 + ft_strcspn(linebuffer + 1, " \t\n|<>$\"'");
	return (add_word_to_tok(linebuffer, len, tok), len);
}
