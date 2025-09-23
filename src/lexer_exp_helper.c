/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_exp_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:13:03 by vramacha          #+#    #+#             */
/*   Updated: 2025/09/23 15:26:17 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lexer.h"

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

static void	free_and_exit(t_lexer *lex, char *str1, char *str2)
{
	free(str1);
	free(str2);
	cleanup_print_error_and_exit(lex);
}

static size_t	incr_lex_and_ret_len_sps(
	const char *val, t_lexer *lex, char *sps, char *sep)
{
	if (!incr_lex(lex))
		free_and_exit(lex, sps, sep);
	return (ft_strspn(val, sps));
}

static size_t	insert_text(
	const char *val, t_lexer *lex, char *end_of_word, char *str)
{
	size_t	i;

	i = insert_plain_text(val, lex, end_of_word, 0);
	if (i == (size_t)-1)
		free_and_exit(lex, end_of_word, str);
	return (i);
}

/* add fields (defined using IFS contents) as tokens */
void	fields_to_words(const char *val, t_env_list *env_list, t_lexer *lex)
{
	char	*sps;
	char	*sep;

	extract_sps_sep_from_ifs(&sps, &sep, env_list, lex);
	if (ft_strspn(val, sps))
		val += incr_lex_and_ret_len_sps(val, lex, sps, sep);
	while (*val)
	{
		if (ft_strcspn(val, sep) < ft_strcspn(val, sps))
			val += 1 + insert_text(val, lex, sep, sps);
		else
		{
			val += insert_text(val, lex, sps, sep);
			if (!*val)
				break ;
		}
		val += incr_lex_and_ret_len_sps(val, lex, sps, sep);
	}
	free(sps);
	free(sep);
}
