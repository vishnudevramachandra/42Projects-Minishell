/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:39:35 by swied             #+#    #+#             */
/*   Updated: 2025/09/10 14:40:26 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

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

/* Helper function to create a new env node */
t_env_node	*create_env_node(char *var, char *val)
{
	t_env_node	*new_node;

	new_node = gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), NULL);
	new_node->variable = ft_strdup(var);
	if (!new_node->variable)
		return (ft_putstr_fd("minishell: malloc failed\n", 2), NULL);
	add_to_gc(new_node->variable);
	if (val)
	{
		new_node->value = ft_strdup(val);
		if (!new_node->value)
			return (ft_putstr_fd("minishell: malloc failed\n", 2), NULL);
		add_to_gc(new_node->value);
	}
	else
		new_node->value = NULL;
	new_node->is_export = 1;
	new_node->next = NULL;
	return (new_node);
}
