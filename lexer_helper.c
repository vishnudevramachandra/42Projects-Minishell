/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vramacha <vramacha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 13:51:59 by vishnudevra       #+#    #+#             */
/*   Updated: 2025/08/27 17:08:35 by vramacha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "./libft/libft.h"
#include "lexer.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*get_env_value(t_env_list *env_list, char *var)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp (current->variable, var) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
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

size_t	extract_var(char **var, const char *linebuffer, t_env_list *env_list)
{
	size_t	len;
	char	*name;

	len = ft_strspn(linebuffer,
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	name = malloc((len + 1) * sizeof(char));
	ft_strlcpy(name, linebuffer, len + 1);
	*var = get_env_value(env_list, name);
	free(name);
	return (len);
}

/* add fields (defined using IFS contents) as tokens */
void	fields_to_words(const char *var, t_env_list *env_list, t_token **tok)
{
	char	*sps;
	char	*sep;

	sps = set_inter(" \t\n", get_env_value(env_list, "IFS"));
	if (!sps)
		cleanup_print_error_and_exit(*tok);
	sep = set_diff(get_env_value(env_list, "IFS"), sps);
	if (!sep)
	{
		free(sps);
		cleanup_print_error_and_exit(*tok);
	}
	if (ft_strspn(var, sps))
	{
		if ((*tok)->type != CHAR_NULL)
		{
			(*tok)->next = malloc(sizeof(t_token));
			if (!(*tok)->next)
				exit(1);
			init_token((*tok)->next);
			*tok = (*tok)->next;
		}
		var += ft_strspn(var, sps);
	}
	while (*var)
	{
		if (ft_strcspn(var, sep) < ft_strcspn(var, sps))
			var += 1 + insert_plain_text(var, *tok, sep);
		else
		{
			var += insert_plain_text(var, *tok, sps);
			if (!*var)
				break ;
		}
		(*tok)->next = malloc(sizeof(t_token));
		if (!(*tok)->next)
			exit(1);
		init_token((*tok)->next);
		*tok = (*tok)->next;
		var += ft_strspn(var, sps);
	}
}

/* Expand parameter/variable and when not enclosed within double quotes turn the
   fields into words */
size_t	expand_p_v(const char *linebuffer, t_token **tok, t_env_list *env_list,
			int sep_fields_into_words)
{
	size_t	len;
	char	*var;

	if (*(linebuffer + 1) == '?')
	{
		//TODO: exit status of most recent foreground execution
		return (2);
	}
	else if (*(linebuffer + 1) == '$')
	{
		add_word_to_tok(linebuffer, 2, *tok);
		return (2);
	}
	else if (ft_isalnum(*(linebuffer + 1)))
	{
		len = 1 + extract_var(&var, linebuffer + 1, env_list);
		if (var)
		{
			if (sep_fields_into_words)
				fields_to_words(var, env_list, tok);
			else
				add_word_to_tok(var, ft_strlen(var), *tok);
		}
		return (len);
	}
	len = 1 + ft_strcspn(linebuffer + 1, " \t\n|<>$\"'"); 
	add_word_to_tok(linebuffer, len, *tok);
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
