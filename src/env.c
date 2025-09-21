/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:49:51 by swied             #+#    #+#             */
/*   Updated: 2025/09/21 16:22:20 by swied            ###   ########.fr       */
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
		if (current->is_export && current->value)
		{
			ft_putstr_fd(current->variable, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}

/* Creates a new_node and gives it the variable and value it gets. */
int	add_env_var(t_env_list *env_list, char *var, char *val)
{
	t_env_node	*new_node;
	t_env_node	*last;

	new_node = create_env_node(var, val);
	if (!new_node)
		return (1);
	env_list->size++;
	if (!env_list->head)
		env_list->head = new_node;
	else
	{
		last = env_list->head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
	return (0);
}

/* deletes value if the variable was there before and fills it with val
+ If no variable there before it calls add_env_var */
int	set_env_var(t_env_list *env_list, char *var, char *val)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->variable, var) == 0)
		{
			if (current->value)
				gc_free(current->value);
			current->value = ft_strdup(val);
			if (!current->value)
				return (ft_putstr_fd("minishell: malloc failed\n", 2), 1);
			add_to_gc(current->value);
			current->is_export = 1;
			return (0);
		}
		current = current->next;
	}
	return (add_env_var(env_list, var, val));
}
