/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 17:38:41 by swied             #+#    #+#             */
/*   Updated: 2025/08/06 19:19:39 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

/* gets variable from *envp. Everything before '=' */
char	*get_variable(char *envp)
{
	char	*new_variable;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (envp[i] && envp[i] != '=')
		i++;
	new_variable = gc_malloc(sizeof(char) * (i + 1));
	if (!new_variable)
		return (NULL);
	while (j < i)
	{
		new_variable[j] = envp[j];
		j++;
	}
	new_variable[j] = '\0';
	return (new_variable);
}

/* gets value form *envp. Everything after '=' */
char	*get_value(char *envp)
{
	char	*new_value;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = 0;
	while (envp[i] != '=')
		i++;
	while (envp[i + len])
		len++;
	new_value = gc_malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return (NULL);
	i++;
	while (envp[i])
	{
		new_value[j] = envp[i];
		j++;
		i++;
	}
	new_value[len] = '\0';
	return (new_value);
}

/* Fills the env_list with nodes. Gets variable and value from *envp */
void	add_env_node(char *envp, t_env_list *env_list)
{
	t_env_node	*new_node;
	t_env_node	*last;

	new_node = gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return ;
	env_list->size++;
	new_node->variable = get_variable(envp);
	new_node->value = get_value(envp);
	new_node->is_export = true;
	new_node->next = NULL;
	if (!env_list->head)
		env_list->head = new_node;
	else
	{
		last = env_list->head;
		while (last->next)
			last = last->next;
		last->next = new_node;
	}
}

/* Creates a env_list and fills it with nodes. Goes through **envp */
t_env_list	*fill_env_list(char **envp)
{
	int			i;
	t_env_list	*env_list;

	i = 0;
	env_list = gc_malloc(sizeof(t_env_list));
	env_list->size = 0;
	env_list->head = NULL;
	while (envp[i])
	{
		add_env_node(envp[i], env_list);
		i++;
	}
	return (env_list);
}
