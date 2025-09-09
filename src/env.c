/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:49:51 by swied             #+#    #+#             */
/*   Updated: 2025/09/09 15:20:40 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* calls print_env and returns it status */
int	builtin_env(t_env_list *env_list)
{
	int	status;

	status = 0;
	status = print_env(env_list);
	return (status);
}

/* prints everything in env_list which is flaged with is_export */
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

/* Creates a new_node and gives it the variable and value it becomes. Not done yet (Case without value + If variable was there before missing) */
int	add_env_var(t_env_list *env_list, char *var, char *val)
{
	t_env_node	*new_node;
	t_env_node	*last;

	new_node = gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
	new_node->variable = ft_strdup(var);
	new_node->value = ft_strdup(val);
	if (!new_node->value || !new_node->variable)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
	add_to_gc(new_node->variable);
	add_to_gc(new_node->value);
	new_node->is_export = true;
	env_list->size++	;
	last = env_list->head;
	while (last->next)
		last = last->next;
	last->next = new_node;
	return (0);
}

/* Searches in the env_list for the variable and returns the value of it */
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

/* deletes value if the variable was there before and fills it with val + If no variable there before it calls add_env_var */
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
