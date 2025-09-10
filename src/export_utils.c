/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:48:05 by swied             #+#    #+#             */
/*   Updated: 2025/09/10 14:49:12 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* Helper function to count exported variables */
int	count_exported_vars(t_env_list *env_list)
{
	t_env_node	*current;
	int			export_count;

	current = env_list->head;
	export_count = 0;
	while (current)
	{
		if (current->is_export)
			export_count++;
		current = current->next;
	}
	return (export_count);
}

/* Bubble sort for the export variable array */
void	bubblesort_array(char **env_array)
{
	int		swapped;
	char	*tmp;
	int		count;
	int		j;

	count = 0;
	while (env_array[count] != NULL)
		count++;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		j = 0;
		while (j < count - 1)
		{
			if (ft_strncmp(env_array[j], env_array[j + 1], ft_strlen(env_array[j])) > 0)
			{
				tmp = env_array[j];
				env_array[j] = env_array[j + 1];
				env_array[j + 1] = tmp;
				swapped = 1;
			}
			j++;
		}
	}
}
