/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 03:18:51 by swied             #+#    #+#             */
/*   Updated: 2025/08/24 03:32:38 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_unset(t_env_list *env_list, t_cmd_node *cmd_node)
{
	int	i;

	i = 1;
	while (cmd_node->cmd[i])
	{
		unset_env_var(env_list, cmd_node->cmd[i]);
		i++;
	}
	return (0);
}

void    unset_env_var(t_env_list *env_list, char *var)
{
	t_env_node	*current;
	t_env_node	*prev;

	current = env_list->head;
	prev = NULL;
	while (current)
	{
		if (ft_strcmp(current->variable, var) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				env_list->head = current->next;
			gc_free(current->variable);
			gc_free(current->value);
			gc_free(current);
			env_list->size--;
			return ;
		}
		prev = current;
		current = current->next;
	}
}
