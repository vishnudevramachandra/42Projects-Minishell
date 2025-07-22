/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 15:49:51 by swied             #+#    #+#             */
/*   Updated: 2025/07/16 15:13:31 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != NULL)
	{
		printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

int	update_env_var(char ***env, char *key, char *value)
{
	char	*new_entry;
	int		key_len;
	int		i;
	
	key_len = ft_strlen(key);
	new_entry = malloc(sizeof(char) * (key_len + ft_strlen(value) + 2));
	if (!new_entry)
		return (ft_putstr_fd("Malloc failed\n", 2), 1);
	ft_strlcpy(new_entry, key, key_len + 1);
	new_entry[key_len] = '=';
	ft_strlcpy(new_entry + key_len + 1, value, ft_strlen(value) + 1);
	i = 0;
	while ((*env)[i])
	{
		if (ft_strncmp((*env)[i], key, key_len) == 0 && (*env)[i][key_len] == '=')
		{
			(*env)[i] = new_entry;
			return (0);
		}
		i++;
	}
	if (add_env_var(env, new_entry, i) == 1)
		return (1);
	return(0);
}

int	add_env_var(char ***env, char *new_entry, int i)
{
	char	**new_env;
	int		j;

	new_env = malloc(sizeof(char*) * (i + 2));
	if (!new_env)
		return(ft_putstr_fd("Malloc failed\n", 2), 1);
	j = 0;
	while (j < i)
	{
		new_env[j] = (*env)[j];
		j++;
	}
	new_env[i] = new_entry;
	new_env[i + 1] = NULL;
	free(*env);
	*env = new_env;
	return (0);
}
