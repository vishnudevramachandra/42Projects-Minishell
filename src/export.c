#include <stddef.h>

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
	char	**env_array;
	if (cmd_node->cmd[1] == NULL)
	{
		env_array = create_export_list(env_list);
		print_export(env_list, env_array, 0);
		free_export_array(env_array, 0);
	}
	else
		printf("mehr als ein cmd-arg\n");
	return (0);
}

/* not done yet | prints out everything in env_list with declare -x before */
void	print_export(t_env_list *env_list, char **env_array, int i)
{
	t_env_node	*current;
	while (env_array[i])
	{
		current = env_list->head;
		while (current)
		{
			if (ft_strcmp(env_array[i], current->variable) == 0)
			{
				ft_putstr_fd("declare -x ", 1);
				ft_putstr_fd(current->variable, 1);
				if (current->value)
				{
					ft_putstr_fd("=\"", 1);
					ft_putstr_fd(current->value, 1);
					ft_putchar_fd('"', 1);
				}
				ft_putchar_fd('\n', 1);
				break ;
			}
			current = current->next;
		}
		i++;
	}
}

/* creates a sorted array of export variable names for export */
char	**create_export_list(t_env_list *env_list)
{
	t_env_node *current;
	char 		**env_array;
	int			i;

	current = env_list->head;
	env_array = malloc(sizeof(char *) * (env_list->size + 1));
	if (!env_array)
		return NULL;
	i = 0;
	while (current)
	{
		env_array[i] = ft_strdup(current->variable);
		i++;
		current = current->next;
	}
	env_array[i] = NULL;
	bubblesort_array(env_array);
	return env_array;
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

/* Free the export array, not allocated with gc */
void	free_export_array(char **array, int i)
{
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
