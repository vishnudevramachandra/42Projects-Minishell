/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:17:26 by swied             #+#    #+#             */
/*   Updated: 2025/07/16 14:51:35 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_cd(char **args, char ***env)
{
	char *target_dir;
	char *current_pwd;
	char	*new_pwd;
	
	(void)env;
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
	{
		perror("minishell: cd: getcwd");
		return (1);
	}
	if (!args[1])
		target_dir = ft_strdup(getenv("HOME"));
	else if (strcmp(args[1], "-") == 0)
		target_dir = ft_strdup(getenv("OLDPWD"));
	else
		target_dir = ft_strdup(args[1]);
	if (!target_dir)
		return (ft_putstr_fd("HOME not set\n", 1), free(current_pwd), 1);
	if (chdir(target_dir) == -1)
		return (ft_putstr_fd("Directory not found", 2), free(current_pwd), free(target_dir), 1);
	update_env_var(env, "OLDPWD", current_pwd);
	new_pwd = getcwd(NULL, 0);
	if (new_pwd)
	{
		update_env_var(env, "PWD", new_pwd);
		free(new_pwd);
	}
	free(current_pwd);
	free(target_dir);
	return (0);
}
