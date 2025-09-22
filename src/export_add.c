/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 04:09:11 by swied             #+#    #+#             */
/*   Updated: 2025/09/22 22:04:30 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	add_export(t_env_list *env_list, t_cmd_node *cmd_node)
{
	int	i;
	int	exit_status;

	i = 1;
	exit_status = 0;
	while (cmd_node->cmd[i])
	{
		exit_status = process_export_arg(env_list, cmd_node->cmd[i]);
		if (exit_status == -1)
			return (-1);
		i++;
	}
	return (exit_status);
}

int	process_export_arg(t_env_list *env_list, char *arg)
{
	int		var_len;
	char	*var;

	var_len = 0;
	if (check_valid_export(arg))
		return (ft_putstr_fd("Invalid export input\n", 2), 1);
	if (!search_for_equal_sign(arg))
		return (handle_export_without_equal(env_list, arg));
	while (arg[var_len] && arg[var_len] != '=')
		var_len++;
	var = ft_substr(arg, 0, var_len);
	if (arg[var_len + 1] == '\0')
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
	t_env_node	*existing;

	existing = find_env_var(env_list, var);
	if (existing)
	{
		if (existing->value)
			gc_free(existing->value);
		existing->value = ft_strdup("");
		if (!existing->value)
			return (-1);
		add_to_gc(existing->value);
		existing->is_export = 1;
		return (0);
	}
	if (!add_env_var(env_list, var, ""))
		return (-1);
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
	t_env_node	*existing;

	existing = find_env_var(env_list, arg);
	if (existing)
	{
		existing->is_export = 1;
		return (0);
	}
	if (!add_env_var(env_list, arg, NULL))
		return (-1);
	return (0);
}
