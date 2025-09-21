/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_to_dblarray.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 18:43:28 by swied             #+#    #+#             */
/*   Updated: 2025/09/21 16:41:02 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* creates a string and strjoins the var + '=' + val in it | Adds it to gc */
int	create_env(char *var, char *value, char **array, int i)
{
	char	*temp;

	temp = ft_strjoin(var, "=");
	if (!temp)
		return (0);
	array[i] = ft_strjoin(temp, value);
	free(temp);
	if (!array[i])
		return (0);
	add_to_gc(array[i]);
	return (1);
}

/* Creates a double array which gets filled with the env_list
and help of create_env */
char	**list_to_dblarray(t_env_list *env_list)
{
	char		**new_envp;
	t_env_node	*current;
	int			i;

	i = 0;
	if (!env_list)
		return (NULL);
	new_envp = gc_malloc(sizeof(char *) * (env_list->size + 1));
	if (!new_envp)
		return (ft_putstr_fd("minishell: malloc failed\n", 1), NULL);
	current = env_list->head;
	while (current)
	{
		if (current->value)
		{
			if (!create_env(current->variable, current->value, new_envp, i))
				return (free_env_array(new_envp, i));
			i++;
		}
		current = current->next;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

/* Frees the env_double_array */
char	**free_env_array(char **array, int i)
{
	while (--i >= 0)
	{
		gc_free(array[i]);
	}
	gc_free(array);
	return (NULL);
}
