/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:49:51 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 18:18:48 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_env(t_env_list *env_list)
{
	int	status;

	status = 0;
	status = print_env(env_list);
	return (status);
}

int	print_env(t_env_list *env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (current->is_export)
		{
			ft_putstr_fd(current->variable, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}

int	add_env_var(t_env_list *env_list, char *var, char *val)
{
	t_env_node	*new_node;
	t_env_node	*last;
	int			var_len;
	int			val_len;

	new_node = gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
	var_len = ft_strlen(var);
	val_len = ft_strlen(val);
	new_node->variable = gc_malloc(sizeof(char) * (var_len + 1));
	new_node->value = gc_malloc(sizeof(char) * (val_len + 1));
	if (!new_node->value || !new_node->variable)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
	new_node->variable = var;
	new_node->variable[var_len] = '\0';
	new_node->value = val;
	new_node->value[val_len] = '\0';
	last = env_list->head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
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

int	set_env_var(t_env_list *env_list, char *var, char *val)
{
	t_env_node	*current;
	int			value_len;

	value_len = ft_strlen(val);
	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->variable, var) == 0)
		{
			gc_free(current->value);
			current->value = gc_malloc(sizeof(char) * value_len);
			if (!current->value)
				return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
			current->value = val;
			return (0);
		}
		current = current->next;
	}
	return (add_env_var(env_list, var, val));
}
