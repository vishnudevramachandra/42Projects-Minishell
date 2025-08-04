/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 16:45:00 by swied             #+#    #+#             */
/*   Updated: 2025/08/04 17:49:44 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_export(t_env_list *env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		ft_putstr_fd(current->variable, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}
