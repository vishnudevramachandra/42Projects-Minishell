/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 21:23:43 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/09/23 10:43:31 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft/libft.h"
#include "../include/lexer.h"
#include "../include/execute.h"

static size_t	extract_val_of_var(
	char **val, const char *linebuffer, t_env_list *env_list, t_lexer *lex)
{
	size_t	len;
	char	*name;

	len = ft_strspn(linebuffer,
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_");
	name = malloc((len + 1) * sizeof(char));
	if (!name)
		cleanup_print_error_and_exit(lex);
	ft_strlcpy(name, linebuffer, len + 1);
	*val = get_env_value(env_list, name);
	free(name);
	return (len);
}

static void	extract_sps_sep_from_ifs(
	char **sps, char **sep, t_env_list *env_list, t_lexer *lex)
{
	char	*ifs;

	ifs = get_env_value(env_list, "IFS");
	if (!ifs || ft_strlen(ifs) < 1)
		ifs = " \t\n";
	*sps = set_inter(" \t\n", ifs);
	if (!*sps)
		cleanup_print_error_and_exit(lex);
	*sep = set_diff(ifs, *sps);
	if (!*sep)
	{
		free(*sps);
		cleanup_print_error_and_exit(lex);
	}
}

/* add fields (defined using IFS contents) as tokens */
static void	fields_to_words(
	const char *val, t_env_list *env_list, t_lexer *lex)
{
	char	*sps;
	char	*sep;

	extract_sps_sep_from_ifs(&sps, &sep, env_list, lex);
	if (ft_strspn(val, sps) && incr_lex(lex))
		val += ft_strspn(val, sps);
	while (*val)
	{
		if (ft_strcspn(val, sep) < ft_strcspn(val, sps))
			val += 1 + insert_plain_text(val, lex, sep);
		else
		{
			val += insert_plain_text(val, lex, sps);
			if (!*val)
				break ;
		}
		incr_lex(lex);
		val += ft_strspn(val, sps);
	}
	free(sps);
	free(sep);
}

static void	add_int_to_tok(int status, t_lexer *lex)
{
	char	*str;

	str = ft_itoa(status);
	if (!str)
		cleanup_print_error_and_exit(lex);
	add_word_to_tok(str, ft_strlen(str), lex);
	free(str);
}

/* Expand parameter/variable and when not enclosed within double quotes turn the
   fields into words */
size_t	expand_p_v(const char *linebuffer, t_lexer *lex, t_mini *mini,
			int sep_fields_into_words)
{
	size_t	len;
	char	*val;

	if (*(linebuffer + 1) == '?')
		return (add_int_to_tok(mini->status, lex), 2);
	else if (*(linebuffer + 1) == '$')
		return (add_word_to_tok(linebuffer, 2, lex), 2);
	else if (ft_isalnum(*(linebuffer + 1)))
	{
		len = 1 + extract_val_of_var(&val, linebuffer + 1, mini->env_list, lex);
		if (val)
		{
			if (sep_fields_into_words)
				fields_to_words(val, mini->env_list, lex);
			else
				add_word_to_tok(val, ft_strlen(val), lex);
		}
		return (len);
	}
	len = 1 + ft_strcspn(linebuffer + 1, " \t\n|<>$\"'");
	return (add_word_to_tok(linebuffer, len, lex), len);
}
