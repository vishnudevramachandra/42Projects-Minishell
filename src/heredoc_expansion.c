/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 14:18:36 by swied             #+#    #+#             */
/*   Updated: 2025/09/22 17:47:56 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static char	*get_empty_str(char *expanded_var)
{
	expanded_var = ft_strdup("");
	if (!expanded_var)
		return (NULL);
	add_to_gc(expanded_var);
	return (expanded_var);
}

/* counts length of potential expansion, calls find_env_value and strjoins
the result */
static char	*process_variable(char *str, t_env_list *env_list, char *result,
	int *i)
{
	int		start;
	int		end;
	char	*var_name;
	char	*expanded_var;

	start = *i + 1;
	end = start;
	while (str[end] && str[end] != ' ' && str[end] != '$' && str[end] != '\t'
		&& str[end] != '\n' && str[end] != '"' && str[end] != '\'')
		end++;
	*i = end;
	var_name = ft_substr(str, start, end - start);
	if (!var_name)
		return (NULL);
	add_to_gc(var_name);
	expanded_var = find_env_value(var_name, env_list);
	if (!expanded_var)
		expanded_var = get_empty_str(expanded_var);
	if (!expanded_var)
		return (NULL);
	result = ft_strjoin(result, expanded_var);
	if (!result)
		return (NULL);
	add_to_gc(result);
	return (result);
}

/* creates substr and returns strjoin of it */
static char	*process_regular_char(char *str, char *result, int *i)
{
	char	*char_str;

	char_str = ft_substr(str, *i, 1);
	if (!char_str)
		return (NULL);
	add_to_gc(char_str);
	result = ft_strjoin(result, char_str);
	if (!result)
		return (NULL);
	add_to_gc(result);
	(*i)++;
	return (result);
}

/* checks for dollar sign in string, if yes -> process_variable.
if no -> handle normal */
char	*check_for_dollar(char *str, t_env_list *env_list, int flag)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	add_to_gc(result);
	while (str[i])
	{
		if (str[i] == '$' && flag == 0)
			result = process_variable(str, env_list, result, &i);
		else
			result = process_regular_char(str, result, &i);
		if (!result)
			return (NULL);
	}
	return (result);
}

/* checks if var_name is in env_list and returns strdup of it */
char	*find_env_value(char *var_name, t_env_list *env_list)
{
	t_env_node	*current_node;
	char		*result;

	if (!var_name || !env_list)
		return (NULL);
	current_node = env_list->head;
	while (current_node)
	{
		if (ft_strcmp(var_name, current_node->variable) == 0)
		{
			result = ft_strdup(current_node->value);
			if (!result)
				return (NULL);
			add_to_gc(result);
			return (result);
		}
		current_node = current_node->next;
	}
	return (NULL);
}
