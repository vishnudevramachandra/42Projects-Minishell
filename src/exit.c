/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: swied <swied@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:58:06 by swied             #+#    #+#             */
/*   Updated: 2025/09/21 16:24:41 by swied            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/execute.h"

static int	is_numstr(char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/* not done yet */
int	builtin_exit(char **args)
{
	int	exit_code;

	exit_code = 0;
	ft_putendl_fd("exit", 1);
	if (args && args[1])
	{
		if (!is_numstr(args[1]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			free_all_garbage();
			rl_clear_history();
			exit(2);
		}
		if (args[2])
		{
			ft_putendl_fd("exit: too many arguments", 2);
			return (1);
		}
		exit_code = ft_atoi(args[1]);
	}
	free_all_garbage();
	rl_clear_history();
	exit(exit_code);
}
