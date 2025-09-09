/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 04:09:11 by swied             #+#    #+#             */
/*   Updated: 2025/09/09 15:21:04 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int add_export(t_env_list *env_list, t_cmd_node *cmd_node)
{
	int i = 1;
	while (cmd_node->cmd[i])
	{
		if (process_export_arg(env_list, cmd_node->cmd[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int process_export_arg(t_env_list *env_list, char *arg)
{
	int var_len;
	int val_len;
	char *var;

	var_len = 0;
	val_len = 0;
	if (!search_for_equal_sign(arg))
		return (handle_export_without_equal(env_list, arg));
	while (arg[var_len] && arg[var_len] != '=')
		var_len++;
	while (arg[var_len + val_len] && arg[var_len + val_len] != ' ')
		val_len++;
	var = ft_substr(arg, 0, var_len);
	if (val_len == 0)
	{
		if (handle_export_without_value(env_list, var) == -1)
			return (free(var), -1);
	}
	else
	{
		if (set_env_var(env_list, var, arg + var_len + 1) == 1)
			return (free(var), -1);
	}
	free(var);
	return (0);
}

int	handle_export_without_value(t_env_list *env_list, char *var)
{
	t_env_node *current;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(var, current->variable) == 0)
		{
			unset_env_var(env_list, var);
			break;
		}
		current = current->next;
	}
	if (!add_env_var(env_list, var, ""))
	{
		free(var);
		return (-1);
	}
	return (0);
}

int	search_for_equal_sign(char *arg)
{
	while (*arg)
	{
		if (*arg == '=')
			return (1);
		arg++;
	}
	return (0);
}

int	handle_export_without_equal(t_env_list *env_list, char *arg)
{
	t_env_node *new_node;
	t_env_node *last;

	new_node = gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return (-1);
	new_node->variable = ft_strdup(arg);
	new_node->value = NULL;
	new_node->next = NULL;
	new_node->is_export = false;
	env_list->size++;
	if (!new_node->variable)
		return (free(new_node), -1);
	add_to_gc(new_node->variable);
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
