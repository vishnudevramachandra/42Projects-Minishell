/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 02:17:26 by swied             #+#    #+#             */
/*   Updated: 2025/08/05 18:20:01 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

int	builtin_cd(char **args, t_env_list *env_list)
{
	char	*target_dir;
	char	*old_pwd;
	char	*new_pwd;

	if (!args[1])
		target_dir = get_env_value(env_list, "HOME");
	else if (ft_strcmp(args[1], "-") == 0)
		target_dir = get_env_value(env_list, "OLDPWD");
	else
		target_dir = args[1];
	old_pwd = getcwd(NULL, 0);
	add_to_gc(old_pwd);
	if (chdir(target_dir))
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		return (ft_putendl_fd(target_dir, 2), 1);
	}
	set_env_var(env_list, "OLDPWD", old_pwd);
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		return (ft_putendl_fd("minishell: cd failed", 2), 1);
	set_env_var(env_list, "PWD", new_pwd);
	return (add_to_gc(new_pwd), 0);
}
