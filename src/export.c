/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:45:00 by swied             #+#    #+#             */
/*   Updated: 2025/08/06 19:28:16 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Not done yet | If only "export" calls print_export */
int	builtin_export(t_env_list *env_list, t_cmd_node *cmd_node)
{
	if (cmd_node->cmd[1] == NULL)
		print_export(env_list);
	else
		printf("mehr als ein cmd-arg\n");
	return (0);
}

/* not done yet | prints out everything in env_list with declare -x before */
void	print_export(t_env_list *env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (current)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->variable, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
}
